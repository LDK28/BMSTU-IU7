#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
int main()
{
    char c;
    int fd1 = open("alphabet.txt", O_RDONLY);
    int fd2 = open("alphabet.txt", O_RDONLY);
    int flag = 1;
    while(flag)
    {
        if (read(fd1, &c, 1) == 1) {
            write(1, &c, 1);
            if (read(fd2, &c, 1) == 1) {
                write(1, &c, 1);
            } else {
                flag = 0;
            }
        } else {
            flag = 0;
        }
    }
    return 0;
}
