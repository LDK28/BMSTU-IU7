@ECHO OFF
CHCP 65001
GCC -std=c99 -Wall -Wpedantic -Wextra -Werror -Wvla -pg -c main.c
GCC -pg -o app.exe main.o

.\app.exe < my_data_1000.txt > out.txt
gprof app.exe > report_1000.txt

.\app.exe < my_data_10000.txt > out.txt
gprof app.exe > report_10000.txt

.\app.exe < my_data_10.txt > out.txt
gprof app.exe > report_10.txt

DEL *.exe *.o

GCC -std=c99 -Wall -Wpedantic -Wextra -Werror -Wvla -O1 -pg -c main.c
GCC -pg -o app.exe main.o
.\app.exe < my_data_10000.txt > out.txt
gprof app.exe > report_10000_O1.txt
DEL *.exe *.o

GCC -std=c99 -Wall -Wpedantic -Wextra -Werror -Wvla -O2 -pg -c main.c
GCC -pg -o app.exe main.o
.\app.exe < my_data_10000.txt > out.txt
gprof app.exe > report_10000_O2.txt
DEL *.exe *.o

GCC -std=c99 -Wall -Wpedantic -Wextra -Werror -Wvla -O3 -pg -c main.c
GCC -pg -o app.exe main.o
.\app.exe < my_data_10000.txt > out.txt
gprof app.exe > report_10000_O3.txt
DEL out.txt
.\make_clean.cmd