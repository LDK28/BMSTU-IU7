@ECHO OFF
CHCP 65001
GCC -std=c99 -Wall -Werror -Wpedantic -Wextra -Wvla -g3 -c main.c
GCC -Wall -Werror -Wpedantic -Wextra -Wvla -g3 -c myfunctions.c
GCC myfunctions.o main.o -o app.exe