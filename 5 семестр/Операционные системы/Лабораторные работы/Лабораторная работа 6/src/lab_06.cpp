#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define OK 0

#define READERS_CNT 5
#define WRITERS_CNT 5

#define WITER_CNT 8
#define RITER_CNT 7

#define WRITE_TIMEOUT 300
#define READ_TIMEOUT 300
#define DIFF 4//000


HANDLE mutex;
HANDLE can_read;
HANDLE can_write;

LONG active_readers = 0;
LONG waiting_writers = 0;
LONG waiting_readers = 0;

BOOL active_writer = 0;
static int value = 0;

void start_read(void) 
{
	InterlockedIncrement(&waiting_readers);
	WaitForSingleObject(can_read, INFINITE);

	if (waiting_readers || (WaitForSingleObject(can_write, 0) == WAIT_OBJECT_0))
		WaitForSingleObject(can_read, INFINITE);

	InterlockedDecrement(&waiting_readers);
	InterlockedIncrement(&active_readers);

	SetEvent(can_read);
	ReleaseMutex(mutex);
}

void stop_read(void) 
{
	InterlockedDecrement(&active_readers);
	if (waiting_readers == 0)
	{
		ResetEvent(can_read);
		SetEvent(can_write);
	}
}

DWORD WINAPI reader(CONST LPVOID lpParams) 
{
	srand(time(NULL) + WRITERS_CNT);
	int sleep_time;

	for (size_t i = 0; i < RITER_CNT; i++)
	{
		sleep_time = READ_TIMEOUT + rand() % DIFF;
		Sleep(sleep_time);
		start_read();
		printf("Reader %d read: %d\n", (int)lpParams, value);
		stop_read();
	}

	return OK;
}

void start_write(void) 
{
	InterlockedIncrement(&waiting_writers);
	WaitForSingleObject(mutex, INFINITE);

	if (active_writer == 1 || active_readers > 0)
		WaitForSingleObject(can_write, INFINITE);

	InterlockedDecrement(&waiting_writers);
	active_writer = 1;

	// ReleaseMutex анлочит ранее залоченный мьютекс
	ReleaseMutex(mutex);
}

void stop_write(void) 
{
	active_writer = 0;

	if (waiting_readers > 0)
		SetEvent(can_read);
	else
		SetEvent(can_write);
}

DWORD WINAPI writer(CONST LPVOID lpParams) 
{
	srand(time(NULL) + READERS_CNT);
	int sleep_time;

	for (int i = 0; i < WITER_CNT; i++)
	{
		sleep_time = WRITE_TIMEOUT + rand() % DIFF;
		Sleep(sleep_time);
		start_write();

		printf("Writer %d write: %d\n", (int)lpParams, ++value);
		stop_write();
	}

	return OK;
}

int main(void) 
{
	HANDLE writers_threads[WRITERS_CNT];
	HANDLE readers_threads[READERS_CNT];

	if ((mutex = CreateMutex(NULL, 0, NULL)) == NULL) 
	{
		perror("CreateMutex error.\n");
		return GetLastError();
	}

	if ((can_read = CreateEvent(NULL, 1, 0, NULL)) == NULL || (can_write = CreateEvent(NULL, 0, 0, NULL)) == NULL) 
	{
		perror("CreateEvent error.\n");
		return GetLastError();
	}

	for (int i = 0; i < READERS_CNT; i++)
	{
		if ((readers_threads[i] = CreateThread(NULL, 0, reader, (LPVOID)i, 0, NULL)) == NULL) 
		{
			perror("CreateThread error.\n");
			return GetLastError();
		}
	}

	for (int i = 0; i < WRITERS_CNT; i++)
	{
		if ((writers_threads[i] = CreateThread(NULL, 0, writer, (LPVOID)i, 0, NULL)) == NULL) 
		{
			perror("CreateThread error.\n");
			return GetLastError();
		}
	}

	WaitForMultipleObjects(READERS_CNT, readers_threads, 1, INFINITE);
	WaitForMultipleObjects(WRITERS_CNT, writers_threads, 1, INFINITE);

	CloseHandle(mutex);
	CloseHandle(can_read);
	CloseHandle(can_write);

	return OK;
}





























































// // Надо использовать неделимые операции:
// // InterLockedIncrement, InterLockedDecrement.
// // В программе должно быть 3 счетчика:
// // ждущих писателей, ждущих читателей и активных читателей.
// // Активный писатель м.б. только один и это логический тип.

// #include <windows.h>
// #include <stdbool.h>
// #include <stdio.h>
// #include <time.h>
// #include <stdbool.h>

// #define OK 0

// #define CREATE_MUTEX_ERROR 1
// #define CREATE_EVENT_ERROR 2
// #define CREATE_READER_THREAD_ERROR 3
// #define CREATE_WRITER_THREAD_ERROR 3

// #define MINIMUM_READER_DELAY 100
// #define MINIMUM_WRITER_DELAY 100
// #define MAXIMUM_READER_DELAY 200
// #define MAXIMUM_WRITER_DELAY 200

// #define READERS_NUMBER 3
// #define WRITERS_NUMBER 3

// #define ITERATIONS_NUMBER 5

// HANDLE canRead;
// HANDLE canWrite;
// HANDLE mutex;

// LONG waitingWritersCount = 0;
// LONG waitingReadersCount = 0;
// LONG activeReadersCount = 0;
// bool writing = false;

// HANDLE readerThreads[READERS_NUMBER];
// HANDLE writerThreads[WRITERS_NUMBER];

// int readersID[READERS_NUMBER];
// int writersID[WRITERS_NUMBER];

// int readersRand[READERS_NUMBER * ITERATIONS_NUMBER];
// int writersRand[READERS_NUMBER * ITERATIONS_NUMBER];

// int value = 0;

// bool turn(HANDLE event)
// {
// 	// Если функция возвращает WAIT_OBJECT_0, объект свободен.
// 	return WaitForSingleObject(event, 0) == WAIT_OBJECT_0;
// }

// void StartRead()
// {
// 	// Увеличиваем кол-во ждущих читателей.
// 	InterlockedIncrement(&waitingReadersCount);

// 	// Процесс читатель сможет начать работать,
// 	// Если есть нет активного писателя,
// 	// И нет писателей, ждущих свою очередь.
// 	WaitForSingleObject(mutex, INFINITE);

// 	if (writing || turn(canWrite))
// 		WaitForSingleObject(canRead, INFINITE);

// 	// Уменьшаем кол-во ждущих читателей.
// 	InterlockedDecrement(&waitingReadersCount);
// 	// Увеличиваем кол-во активных читателей.
// 	InterlockedIncrement(&activeReadersCount);
// 	// Выдаем сигнал canRead,
// 	// Чтобы следующий читатель в очереди
// 	// Читателей смог начать чтение
// 	SetEvent(canRead);
// 	ReleaseMutex(mutex);
// }

// void StopRead()
// {
// 	// Уменьшаем количество активных читателей.
// 	InterlockedDecrement(&activeReadersCount);
// 	// Если число читателей равно нулю,
// 	// Выполняется signal(can_write),
// 	// активизирующий писателя из очереди писателей.
// 	if (!activeReadersCount)
// 	{
// 		ResetEvent(canRead);
// 		SetEvent(canWrite);
// 	}
// }

// DWORD WINAPI Reader(CONST LPVOID param)
// {
// 	int id = *(int *)param;
// 	int sleepTime;
// 	int begin = id * ITERATIONS_NUMBER;
// 	for (int i = 0; i < ITERATIONS_NUMBER; i++)
// 	{
// 		sleepTime = readersRand[begin + i];
// 		StartRead();
// 		printf("Reader with id = %d; value = %d; sleep time = %d.\n", id, value, sleepTime);
// 		StopRead();

// 		Sleep(sleepTime);
// 	}
// }

// void StartWrite()
// {
// 	// Увеличиваем кол-во ждущих писателей.
// 	InterlockedIncrement(&waitingWritersCount);

// 	// Процесс писатель сможет начать работать,
// 	// Если нет читающих процессов
// 	// И нет другого активного писателя.
// 	if (activeReadersCount > 0 || writing)
// 		WaitForSingleObject(canWrite, INFINITE);

// 	// Уменьшаем кол-во ждущих писателей.
// 	InterlockedDecrement(&waitingWritersCount);
// 	// Писатель пишет.
// 	writing = true;
// }

// void StopWrite()
// {
// 	writing = false;

// 	if (waitingReadersCount)
// 		SetEvent(canRead);
// 	else
// 		SetEvent(canWrite);
// }

// DWORD WINAPI Writer(CONST LPVOID param)
// {
// 	int id = *(int *)param;
// 	int sleepTime;
// 	int begin = id * ITERATIONS_NUMBER;
// 	for (int i = 0; i < ITERATIONS_NUMBER; i++)
// 	{
// 		sleepTime = writersRand[begin + i];

// 		StartWrite();
// 		++value;
// 		printf("Writer with id = %d; value = %d; sleep time = %d.\n", id, value, sleepTime);
// 		StopWrite();

// 		Sleep(sleepTime);
// 	}
// }

// int InitHandles()
// {
// 	// 2ой аргумент == false значит мьютекс свободный.
// 	if ((mutex = CreateMutex(NULL, FALSE, NULL)) == NULL)
// 	{
// 		perror("CreateMutex");
// 		return CREATE_MUTEX_ERROR;
// 	}

// 	// 2ой аргумент == FALSE значит автоматический сброс.
// 	// 3ий аргумент == FALSE значит, что объект не в сигнальном состоянии.
// 	if ((canRead = CreateEvent(NULL, TRUE, FALSE, NULL)) == NULL)
// 	{
// 		perror("CreateEvent (canRead)");
// 		return CREATE_EVENT_ERROR;
// 	}

// 	if ((canWrite = CreateEvent(NULL, FALSE, FALSE, NULL)) == NULL)
// 	{
// 		perror("CreateEvent (canWrite)");
// 		return CREATE_EVENT_ERROR;
// 	}

// 	return OK;
// }

// int CreateThreads()
// {
// 	DWORD id = 0;
// 	for (int i = 0; i < READERS_NUMBER; i++)
// 	{
// 		readersID[i] = i;
// 		// Параметры слева направо:
// 		// NULL - Атрибуты защиты определены по умолчанию;
// 		// 0 - размер стека устанавливается по умолчанию;
// 		// Reader - определяет адрес функции потока, с которой следует начать выполнение потока;
// 		// readersID + i - указатель на переменную, которая передается в поток;
// 		//  0 - исполнение потока начинается немедленно;
// 		// Последний - адрес переменной типа DWORD, в которую функция возвращает идентификатор потока.
// 		if ((readerThreads[i] = CreateThread(NULL, 0, &Reader, readersID + i, 0, &id)) == NULL)
// 		{
// 			perror("CreateThread (reader)");
// 			return CREATE_READER_THREAD_ERROR;
// 		}
// 		// printf("Created reader with thread id = %d\n", id);
// 	}

// 	for (int i = 0; i < WRITERS_NUMBER; i++)
// 	{
// 		writersID[i] = i;
// 		if ((writerThreads[i] = CreateThread(NULL, 0, &Writer, writersID + i, 0, &id)) == NULL)
// 		{
// 			perror("CreateThread (writer)");
// 			return CREATE_WRITER_THREAD_ERROR;
// 		}
// 		// printf("Created writer with thread id = %d\n", id);
// 	}

// 	return OK;
// }

// void Close()
// {
// 	// Закрываем дескрипторы mutex, event и всех созданных потоков.
// 	for (int i = 0; i < READERS_NUMBER; i++)
// 		CloseHandle(readerThreads[i]);

// 	for (int i = 0; i < WRITERS_NUMBER; i++)
// 		CloseHandle(writerThreads[i]);

// 	CloseHandle(canRead);
// 	CloseHandle(canWrite);
// 	CloseHandle(mutex);
// }

// void CreateRand()
// {
// 	for (int i = 0; i < READERS_NUMBER * ITERATIONS_NUMBER; i++)
// 		readersRand[i] = rand() % (MAXIMUM_READER_DELAY - MINIMUM_READER_DELAY) + MINIMUM_READER_DELAY;

// 	for (int i = 0; i < WRITERS_NUMBER * ITERATIONS_NUMBER; i++)
// 		writersRand[i] = rand() % (MAXIMUM_WRITER_DELAY - MINIMUM_WRITER_DELAY) + MINIMUM_WRITER_DELAY;
// }

// int main(void)
// {
// 	setbuf(stdout, NULL);
// 	srand(time(NULL));

// 	CreateRand();

// 	int err = InitHandles();
// 	if (err)
// 		return err;

// 	err = CreateThreads();
// 	if (err)
// 		return err;

// 	// READERS_NUMBER - кол-во инетерсующих нас объектов ядра.
// 	// readerThreads - указатель на массив описателей объектов ядра.
// 	// TRUE - функция не даст потоку возобновить свою работу, пока не освободятся все объекты.
// 	// INFINITE - указывает, сколько времени поток готов ждать освобождения объекта.
// 	WaitForMultipleObjects(READERS_NUMBER, readerThreads, TRUE, INFINITE);
// 	WaitForMultipleObjects(WRITERS_NUMBER, writerThreads, TRUE, INFINITE);

// 	Close();

// 	printf("\nOk!\n");
// 	return OK;
// }