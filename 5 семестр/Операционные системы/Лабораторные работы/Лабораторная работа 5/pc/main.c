#include <stdio.h>
#include <stdlib.h>	 // rand()
#include <pthread.h> // time()
#include <unistd.h>
#include <sys/wait.h>
#include <sys/sem.h>
#include <sys/stat.h>
#include <sys/shm.h>

#include "constants.h"

#include "consumer.h"
#include "producer.h"ё
#include "delay.h"
#include "buffer.h"

struct sembuf InitValue[2] = {
	{SB, 1, SEM_FLG}, // SB изначально установлен в 1.
	{SE, N, SEM_FLG}  // SE изначально равно N.
};

int *cons_pos = NULL;
int *prod_pos = NULL;
char *buf = NULL;

const int shm_size = 2 * sizeof(int) + N * sizeof(char);

int main(void)
{
	srand(time(NULL));

	int semDescr;
	int status;
	int perms = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	int *address = NULL;

	Delay *delaysProducer = CreateRandomDelays(NUMBER_OF_WORKS, PRODUCER_DELAY_TIME);
	Delay *delaysConsumer = CreateRandomDelays(NUMBER_OF_WORKS, CONSUMER_DELAY_TIME);

	// IPC_PRIVATE - ключ, который показывает, что
	// Набор семафоров могут использовать только процессы,
	// Порожденные процессом, создавшим семафор.

	// shmget - создает новый разделяемый сегмент.
	int shmid = shmget(IPC_PRIVATE, shm_size, perms);
	if (shmid == -1)
	{
		perror("Не удалось создать разделяемый сегмент.\n");
		return ERROR;
	}

	// Функция shmat() возвращает указатель на сегмент
	// shmaddr (второй аргумент) равно NULL,
	// то система выбирает подходящий (неиспользуемый)
	// адрес для подключения сегмента.
	address = shmat(shmid, NULL, 0);
	if (*(char *)address == -1)
	{
		perror("Не удалось получить указатель на сегмент.");
		return ERROR;
	}

	// В начале разделяемой памяти хранится
	// prod_pos и cons_pos
	// Начиная с buf уже хранятся данные.
	prod_pos = address;
	(*prod_pos) = 0;
	cons_pos = address + sizeof(int);
	(*cons_pos) = 0;
	buf = (char *)(address + 2 * sizeof(int));

	Initbuf(buf);

	// Создаем новый набор, состоящий из 3 семафоров.
	semDescr = semget(IPC_PRIVATE, SEM_COUNT, IPC_CREAT | perms);

	if (semDescr == -1)
	{
		perror("Ошибка при создании набора семафоров.");
		return ERROR;
	}

	// Задаем начальные значения семафоров.
	if (semop(semDescr, InitValue, 2))
	{
		perror("Ошибка при попытке изменить семафор.");
		return ERROR;
	}

	for (int i = 0; i < COUNT; i++)
	{
		CreateProducer(i + 1, semDescr, delaysProducer);
		CreateConsumer(i + 1, semDescr, delaysConsumer);

		// Обновляем задержки.
		UpdateDelays(delaysProducer, PRODUCER_DELAY_TIME);
		UpdateDelays(delaysConsumer, CONSUMER_DELAY_TIME);
	}

	for (int i = 0; i < COUNT_PRODUCER + COUNT_CONSUMER; i++)
		wait(&status);

	printf("Finish\n");

	DestroyDelay(delaysProducer);
	DestroyDelay(delaysConsumer);

	if (shmctl(shmid, IPC_RMID, NULL))
	{
		perror("Ошибка.");
		return ERROR;
	}

	if (shmdt(address) == -1)
	{
		perror("Ошибка при попытке отключить разделяемый сегмент от адресного пространства процесса.");
		return ERROR;
	}

	if (semctl(semDescr, 0, IPC_RMID) == -1)
	{
		perror("Ошибка при попытке удаления семафора.");
		return ERROR;
	}

	return 0;
}
