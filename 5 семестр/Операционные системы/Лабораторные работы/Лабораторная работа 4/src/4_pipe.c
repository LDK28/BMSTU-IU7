#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

#define SLEEP_TIME 2
#define LEN 8
#define N 2

void check_status(int status, int num_proc)
{
	if (WIFEXITED(status))
		printf("Child process №%d finished with code: %d\n",
			   num_proc, WEXITSTATUS(status));

	if (WIFSIGNALED(status))
		printf("Child process №%d finished from signal: %d\n",
			   num_proc, WTERMSIG(status));

	if (WIFSTOPPED(status))
		printf("Child process №%d finished stopped with code: %d\n",
			   num_proc, WSTOPSIG(status));
}

int main()
{
	setbuf(stdout, NULL);

	int fd[N];
	pid_t childpid_1, childpid_2;

	const char *const messages[N] = {"qwerty\n", "1 234\n"};

	if (pipe(fd) == -1)
	{
		perror("Can't pipe.\n");
		return 1;
	}

	printf("Parent process PID: %d, GROUP: %d\n",
		   getpid(), getpgrp());

	if ((childpid_1 = fork()) == -1)
	{
		perror("Can\'t fork.\n");
		return 1;
	}
	else if (childpid_1 == 0)
	{
		close(fd[0]);
		write(fd[1], messages[0], strlen(messages[0]));
		printf("Message №1 has been sent to parent\n");
		return 0;
	}

	if ((childpid_2 = fork()) == -1)
	{
		perror("Can\'t fork.\n");
		return 1;
	}
	else if (childpid_2 == 0)
	{
		close(fd[0]);
		write(fd[1], messages[1], strlen(messages[1]));
		printf("Message №2 has been sent to parent\n");
		return 0;
	}

	int status;

	childpid_1 = wait(&status);
	printf("Child process (PID: %d) finished. Status: %d\n",
		   childpid_1, status);
	check_status(status, 1);

	childpid_2 = wait(&status);
	printf("Child process (PID: %d) finished. Status: %d\n",
		   childpid_2, status);
	check_status(status, 2);

	close(fd[1]);

	char message1[LEN], message2[LEN];

	read(fd[0], message1, strlen(messages[0]));
	read(fd[0], message2, strlen(messages[1]));

	printf("Messages:\n");
	printf("%s", message1);
	printf("%s", message2);
	printf("Parent Process is dead.\n");

	return 0;
}
