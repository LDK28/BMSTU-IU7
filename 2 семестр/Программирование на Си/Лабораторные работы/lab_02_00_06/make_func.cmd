@ECHO OFF
CHCP 65001
GCC -std=c99 -Wall -Wpedantic -Wextra -Werror -Wvla -c main.c
GCC -o app.exe main.o
.\app.exe < my_data_10.txt > out_10.txt
.\app.exe < my_data_1000.txt > out_1000.txt
.\app.exe < my_data_10000.txt > out_10000.txt
.\app.exe < my_data_100000.txt > out_100000.txt