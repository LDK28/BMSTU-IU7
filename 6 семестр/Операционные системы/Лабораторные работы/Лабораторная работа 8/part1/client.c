#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>

#define SOCKET_NAME "/home/ldk/Рабочий стол/lab8_os/part1/server.soc"

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("./client.out <message>\n");
        return -1;
    }
    
    int sfd = socket(AF_UNIX, SOCK_DGRAM, 0);
    if (sfd == -1)
    {
        perror("socket call error");
        return errno;
    }

    struct sockaddr_un addr;
    addr.sun_family = AF_UNIX;
    
    strcpy(addr.sun_path, SOCKET_NAME);
    printf("sun_path=%s, len=%d\n", addr.sun_path, strlen(SOCKET_NAME));
    if (connect(sfd, (struct sockaddr *)&addr, sizeof(addr)) == -1)
    {
        perror("Can't set dest address");
        return errno;
    }

    char *msg = argv[1];
    if (send(sfd, msg, strlen(msg), 0) == -1)
    {
        perror("send call error");
        return errno;
    }
    else
    {
        printf("send message: %s\n", msg);
    }

    if (send(sfd, msg, strlen(msg), 0) == -1)
    {
        perror("send call error");
        return errno;
    }
    else
    {
        printf("send message: %s\n", msg);
    }

    close(sfd);

    return 0;
}