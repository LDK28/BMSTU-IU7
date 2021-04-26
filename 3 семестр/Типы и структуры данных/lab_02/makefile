CC := gcc
INCPATH := ./inc/
OBJPATH := ./out/
SRCPATH := ./src/
CFLAGS := -std=c99 --coverage -I$(INCPATH) -Wall -Wpedantic -Wextra -ggdb -g3 -c
LFLAGS := --coverage
APPOBJS := $(OBJPATH)main.o $(OBJPATH)input.o $(OBJPATH)sort.o $(OBJPATH)struct.o
.PHONY: clean
.NOTPARALLEL: release debug

release: CFLAGS := -std=c99 -I$(INCPATH) -o2 -c
release: LFLAGS := -o2
release: $(OBJPATH) $(OBJPATH)release.lastbuildstate app.exe

debug: $(OBJPATH) $(OBJPATH)debug.lastbuildstate app.exe

$(OBJPATH)debug.lastbuildstate: $(OBJPATH)
	rm -fv *.exe
	rm -fv $(OBJPATH)*.o
	rm -fv $(OBJPATH)*.gcno
	rm -fv $(OBJPATH)*.gcda
	rm -fv $(OBJPATH)release.lastbuildstate
	touch $(OBJPATH)debug.lastbuildstate

$(OBJPATH)release.lastbuildstate: $(OBJPATH)
	rm -fv *.exe
	rm -fv $(OBJPATH)*.o
	rm -fv $(OBJPATH)*.gcno
	rm -fv $(OBJPATH)*.gcda
	rm -fv $(OBJPATH)debug.lastbuildstate
	touch $(OBJPATH)release.lastbuildstate

app.exe: $(OBJPATH) $(APPOBJS)
	$(CC) $(LFLAGS) -o app.exe $(APPOBJS)

$(OBJPATH)input.o: $(SRCPATH)input.c
	$(CC) $(CFLAGS) -o $(OBJPATH)input.o $(SRCPATH)input.c

$(OBJPATH)sort.o: $(SRCPATH)sort.c
	$(CC) $(CFLAGS) -o $(OBJPATH)sort.o $(SRCPATH)sort.c

$(OBJPATH)struct.o: $(SRCPATH)struct.c
	$(CC) $(CFLAGS) -o $(OBJPATH)struct.o $(SRCPATH)struct.c

$(OBJPATH)main.o: $(SRCPATH)main.c
	$(CC) $(CFLAGS) -o $(OBJPATH)main.o $(SRCPATH)main.c

dirs: $(INCPATH) $(OBJPATH) $(SRCPATH)

$(OBJPATH):
	mkdir $(OBJPATH)

$(INCPATH):
	mkdir $(INCPATH)

$(SRCPATH):
	mkdir $(SRCPATH)

clean:
	rm -fv *.exe
	rm -fv *.stackdump
	rm -fr $(OBJPATH)
	rm -fr ./.vscode/