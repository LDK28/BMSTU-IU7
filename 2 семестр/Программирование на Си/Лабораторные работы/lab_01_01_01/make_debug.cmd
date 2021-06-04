@ECHO OFF
CHCP 65001
GCC -std=c99 -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -g3 -c main.c
GCC -o app.exe main.o