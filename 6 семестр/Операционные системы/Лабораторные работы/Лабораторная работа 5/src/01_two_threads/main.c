#include <stdio.h>
#include <fcntl.h>
#include <pthread.h>
void thread(int args[2])
{
    FILE *fs = fdopen(args[0], "r");
    char buff[20];
    setvbuf(fs, buff, _IOFBF, 20);

    char c;
    int flag = fscanf(fs, "%c", &c);
    while (flag == 1) {
        fprintf(stdout, "thread %d: %c\n", args[1], c);
        flag = fscanf(fs, "%c", &c);
    }
}
int main() {
    int fd = open("alphabet.txt", O_RDONLY);

    pthread_t tid[2];
    int data1[2] = {fd, 1};
    int data2[2] = {fd, 2};
    for (int i = 0; i < 2; i++) {
        int *data = i == 0 ? data1 : data2;
        if (pthread_create(&tid[i], NULL, thread, data)) {
            printf("Error: can't create thread\n");
            return -1; }
    }
    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);
    return 0;
}