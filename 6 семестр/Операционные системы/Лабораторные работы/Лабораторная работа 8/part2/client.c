#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>
#include <errno.h>

#include "socket.h"


int main(int argc, char *argv[])
{
	setbuf(stdout, NULL);

	struct sockaddr_in serv_addr =
		{
			.sin_family = AF_INET,
			.sin_addr.s_addr = INADDR_ANY,
			.sin_port = htons(PORT)};

	char buf[MAX_LEN_BUF];
	int sock;

	sock = socket(AF_INET, SOCK_STREAM, 0);

	if (socket < 0)
	{
		perror("Error: socket() failed");
		return -1;
	}

	// Устанавливаем соединение. После установки соединения
	// сокет готов к передаче и приему данных.
	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
	{
		printf("Error: connect() failed: %d", errno);
		return -1;
	}

	int bytes;
	char bufServer[BUFSIZ];

	while (TRUE)
	{
		printf("Введите число: ");
		scanf("%s", buf);

		if (send(sock, buf, strlen(buf) + 1, 0) < 0)
		{
			perror("Error: sendto() failed");
			return -1;
		}

		printf("Число отправлено!\n");


		bytes = recv(sock, bufServer, sizeof(bufServer), 0);

		printf("\nОтвет сервера: %s\n\n", bufServer);
	}

	close(sock);

	return 0;
}
