#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>
void thread()
{
    char c;
    int fd = open("alphabet.txt", O_RDONLY);
    while (read(fd, &c, 1) == 1)
    {
        write(1, &c, 1);
    }
}
int main()
{
    pthread_t tid[2];
    for (int i = 0; i < 2; i++) {
        if (pthread_create(&tid[i], NULL, thread, NULL)) {
            printf("Error: can't create thread\n");
            return -1; }
    }
    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);
    return 0;
}
