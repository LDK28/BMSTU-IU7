#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

#define SLEEP_TIME 2
#define LEN 32
#define N 2

int mode = 0;

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

void sig_handler(int sigint)
{
	mode = 1;
	printf("SIGINT\n");
}

int main()
{
	setbuf(stdout, NULL);
	
	int fd[N];
	pid_t childpid_1, childpid_2;
	
const char *const messages[N] = {"qwerty\n", "XXXXXXXXXXXXXXXXXX\n"};
	
	printf("Press Ctrl + C to send messages.\n");
	
	signal(SIGINT, sig_handler);
	sleep(SLEEP_TIME);
	
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
		sleep(SLEEP_TIME);
			
		if (mode)
		{
			close(fd[0]);
			write(fd[1], messages[0], strlen(messages[0]));
			printf("Message №1 has been sent to parent.\n");
		}
	  	else
		  	printf("No signal.\n");
		
	  return 0;
	}

	if ((childpid_2 = fork()) == -1)
	{
		perror("Can\'t fork.\n");
		return 1;
	}
	else if (childpid_2 == 0)
	{
	  	sleep(SLEEP_TIME);
		
	  	if (mode)
	  	{
		  	close(fd[0]);
		  	write(fd[1], messages[1], strlen(messages[1]));
		  	printf("Message №2 has been sent to parent.\n");
	  	}
	  	else
		  	printf("No signal.\n");
		
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
	
	printf("Press Ctrl + C for read from pipe.\n");
	sleep(SLEEP_TIME);
	
	if (mode)
	{
		close(fd[1]);

		char message[LEN] = {0};
		read(fd[0], message, strlen(messages[0]));
		printf("Message 1:\n");
		printf("%s", message);

		char message2[LEN] = {0};
		read(fd[0], message2, strlen(messages[1]));
		printf("Message 2:\n");
		printf("%s", message2);

		char message3[LEN] = {0};
		read(fd[0], message3, 32);
		printf("Messages:\n");
		printf("%s", message3);

	}
	else
		printf("Ctrl + C was not pressed.\n");

	printf("Parent Process is dead.\n");

	return 0;
}