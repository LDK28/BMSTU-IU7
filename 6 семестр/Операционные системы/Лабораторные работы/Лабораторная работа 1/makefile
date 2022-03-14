CC=gcc
WORKDIR=src
FLAGS=-Wall -Werror -pthread

app.exe:
	$(CC) $(FLAGS) $(WORKDIR)/main.c -o app.exe

run: app.exe
	./app.exe

log:
	sudo cat /var/log/syslog

signal:
	sudo kill -s hup 17998

clean:
	rm *.out *.exe *.o