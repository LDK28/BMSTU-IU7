@ECHO OFF
CHCP 65001
GCC -std=c99 -Wall -Wpedantic -Wextra -Werror -Wvla -c main.c
GCC -o app.exe main.o
