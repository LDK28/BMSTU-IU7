CC := gcc
INCPATH := ./inc/
OBJPATH := ./out/
SRCPATH := ./src/
CFLAGS := -std=c99 --coverage -I$(INCPATH) -Wall -Wpedantic -Wextra -ggdb -g3 -c
LFLAGS := --coverage
APPOBJS := $(OBJPATH)main.o $(OBJPATH)list_stack.o $(OBJPATH)array_stack.o $(OBJPATH)utility.o
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

$(OBJPATH)array_stack.o: $(SRCPATH)array_stack.c
	$(CC) $(CFLAGS) -o $(OBJPATH)array_stack.o $(SRCPATH)array_stack.c

$(OBJPATH)list_stack.o: $(SRCPATH)list_stack.c
	$(CC) $(CFLAGS) -o $(OBJPATH)list_stack.o $(SRCPATH)list_stack.c

$(OBJPATH)utility.o: $(SRCPATH)utility.c
	$(CC) $(CFLAGS) -o $(OBJPATH)utility.o $(SRCPATH)utility.c

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