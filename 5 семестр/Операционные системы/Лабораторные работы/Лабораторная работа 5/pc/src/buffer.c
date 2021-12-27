#include <stdio.h>

#include "constants.h"

extern char *buf;

void bufState(char *buf)
{
	printf("Состояние буфера: ");
	for (int i = 0; i < N; i++)
	{
		printf("%c ", *(buf));
		buf++;
	}
	puts("");
}

void Initbuf(char *buf)
{
	for (int i = 0; i < N; i++)
	{
		*buf = '0';
		buf++;
	}
}