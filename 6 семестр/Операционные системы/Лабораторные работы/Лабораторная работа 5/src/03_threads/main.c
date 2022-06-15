#include <stdio.h>
#include <sys/stat.h>
#include <pthread.h>
#define FMT_STR " FS%d: inode = %ld, size = %ld\n"
void *thread(int data) {
    int fid = (int)data;
    struct stat statbuf;
    FILE *fs = fopen("out.txt", "w");
    stat("out.txt", &statbuf);

    printf("FOPEN " FMT_STR, fid, statbuf.st_ino, statbuf.st_size);
    for (char c = 'a'; c <= 'z'; c++) {
        if ((c % 2) == (fid == 1))
            fprintf(fs, "%c", c);
    }
    fclose(fs);
    stat("out.txt", &statbuf);
    printf("FCLOSE" FMT_STR, fid, statbuf.st_ino, statbuf.st_size);
}
int main() {
    pthread_t tid[2]; int fid[2] = {0, 1};
    for (int i = 0; i < 2; i++) {
        if (pthread_create(&tid[i], NULL, thread, fid[i])) {
            printf("Error: can't create thread\n");
            return -1; }
    }
    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL); return 0;
}