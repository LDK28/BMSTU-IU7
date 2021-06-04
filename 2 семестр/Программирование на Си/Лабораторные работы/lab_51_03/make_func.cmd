@ECHO OFF
CHCP 65001
GCC -std=c99 -Wall -Wpedantic -Wextra -Werror -Wvla -O0 --coverage main.c myfunctions.c -o app.exe
PUSHD func
CALL ./all_test.cmd
PUSHD ..
gcov main.c myfunctions.c
