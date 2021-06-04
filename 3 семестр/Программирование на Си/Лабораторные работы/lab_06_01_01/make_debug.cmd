@ECHO OFF
CHCP 65001
GCC -std=c99 -Wall -Werror -Wpedantic -Wextra -Wvla -g3 -c main.c
GCC -std=c99 -Wall -Werror -Wpedantic -Wextra -Wvla -g3 -c films.c
GCC films.o main.o -o app.exe