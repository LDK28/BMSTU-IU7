#include <stdio.h>
#include <sys/stat.h>
#include <pthread.h>
#include <unistd.h>

#define FMT_STR " FS%d: inode = %ld, size = %ld\n"
pthread_mutex_t lock;
void *thread(int data) {
    int fid = (int)data;
    struct stat statbuf;
    FILE *fs = fopen("out.txt", "w");
    stat("out.txt", &statbuf);

    printf("FOPEN " FMT_STR, fid, statbuf.st_ino, statbuf.st_size);
    for (char c = 'a'; c <= 'z'; c++) {
        if ((c % 2) == (fid == 1)) {
            pthread_mutex_lock(&lock);
            lseek(fileno(fs), NULL, SEEK_END);
            fprintf(fs, "%c", c);
            pthread_mutex_unlock(&lock);
        }
    }
    fclose(fs);
    stat("out.txt", &statbuf);
    printf("FCLOSE" FMT_STR, fid, statbuf.st_ino, statbuf.st_size);
}
int main() {
    if (pthread_mutex_init(&lock, NULL) != 0)
    {
        printf("\n mutex init failed\n");
        return 1;
    }
    pthread_t tid[2]; int fid[2] = {0, 1};
    for (int i = 0; i < 2; i++) {
        if (pthread_create(&tid[i], NULL, thread, fid[i])) {
            printf("Error: can't create thread\n");
            return -1; }
    }
    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL); return 0;
}