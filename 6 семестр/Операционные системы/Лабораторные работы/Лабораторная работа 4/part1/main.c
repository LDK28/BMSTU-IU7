#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#define BUF_SIZE 512

void write_from_file_to_file(FILE *from, FILE *to)
{
    int len, i;
    char buf[BUF_SIZE];
    while ((len = fread(buf, 1, BUF_SIZE, from)) > 0)
    {
        for (i = 0; i < len; i++)
            if (buf[i] == 0)
                buf[i] = 10;
        buf[len] = 0;
        fprintf(to, "%s", buf);
    }
}

void write_stat(FILE *from, FILE *to)
{
    char buf[BUF_SIZE];
    fread(buf, 1, BUF_SIZE, from);
    char *pch = strtok(buf, " ");

    while (pch != NULL)
    {
        fprintf(to, "%s\n", pch);
        pch = strtok(NULL, " ");
    }
}

void write_comm(FILE *from, FILE *to)
{
    char buf[BUF_SIZE];
    fscanf(from, "%s", buf);
    fprintf(to, "%s", buf);
}

void null_buf(char *buf)
{
    for (int i = 0; i < BUF_SIZE; i++)
        buf[i] = '\0';
}

void write_dir(char *dirpath, FILE *to)
{
    struct dirent *dirp;
    DIR *dp;
    char buf[BUF_SIZE];
    char path[BUF_SIZE];
    dp = opendir(dirpath);
    while ((dirp = readdir(dp)) != NULL)
    {
        if ((strcmp(dirp->d_name, ".") != 0) && (strcmp(dirp->d_name, "..") != 0))
        {
            sprintf(path, "%s%s", "/proc/4154/fd/", dirp->d_name);
            readlink(path, buf, BUF_SIZE);
            fprintf(to, "%s -> %s\n", dirp->d_name, buf);
        }
        null_buf(buf);
    }
    closedir(dp);
}

int main(int argc, char *argv[])
{
    FILE *s = fopen("/home/ldk/Загрузки/LR4/part1/result1.txt", "w");
    FILE *f;

    fprintf(s, "\n---------------------\nCMDLINE\n---------------------\n");
    f = fopen("/proc/4154/cmdline", "r");
    write_from_file_to_file(f, s);
    fclose(f);

    f = fopen("/proc/4154/environ", "r");
    fprintf(s, "\n---------------------\nENVIRON\n---------------------\n");
    write_from_file_to_file(f, s);
    fclose(f);

    fprintf(s, "\n---------------------\nFD\n---------------------\n");
    write_dir("/proc/4154/fd", s);

    fprintf(s, "\n---------------------\nROOT\n---------------------\n");
    char buf[BUF_SIZE];
    readlink("/proc/4154/root", buf, BUF_SIZE);
    fprintf(s, "%s -> %s\n", "/proc/7531/root", buf);

    f = fopen("/proc/4154/stat", "r");
    fprintf(s, "\n---------------------\nSTAT\n---------------------\n");
    write_stat(f, s);
    fclose(f);

    f = fopen("/proc/4154/maps", "r");
    fprintf(s, "\n---------------------\nMAPS\n---------------------\n");
    write_from_file_to_file(f, s);
    fclose(f);

    // fprintf(s, "\n---------------------\nPAGEMAP\n---------------------\n");

    f = fopen("/proc/4154/comm", "r");
    fprintf(s, "\n---------------------\nCOMM\n---------------------\n");
    write_comm(f, s);
    fclose(f);

    f = fopen("/proc/4154/io", "r");
    fprintf(s, "\n---------------------\nIO\n---------------------\n");
    write_from_file_to_file(f, s);
    fclose(f);

    f = fopen("/proc/4154/wchan", "r");
    fprintf(s, "\n---------------------\nWCHAN\n---------------------\n");
    write_from_file_to_file(f, s);
    fclose(f);

    fprintf(s, "\n---------------------\nTASK\n---------------------\n");
    write_dir("/proc/4154/task", s);

    fclose(s);
    return 0;
}