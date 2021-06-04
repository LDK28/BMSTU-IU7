@ECHO OFF
CHCP 65001
GCC -std=c99 -Wall -Werror -Wpedantic -Wextra -Wvla -c main.c
GCC -std=c99 -Wall -Werror -Wpedantic -Wextra -Wvla -c films.c
GCC films.o main.o -o app.exe