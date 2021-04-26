CC := gcc
INCPATH := ./inc/
OBJPATH := ./out/
SRCPATH := ./src/
FUNCTESTSPATH := ./func_tests/
UNITTESTSPATH := ./unit_tests/
CFLAGS := -std=c99 --coverage -I$(INCPATH) -Wall -Wpedantic -Werror -Wextra -ggdb -g3 -c
LFLAGS := --coverage
LCHECKFLAGS := -lcheck -lpthread
APPOBJS := $(OBJPATH)mysnprintf.o
UNITTESTSOBJS := $(OBJPATH)check_mysnprintf.o $(OBJPATH)mysnprintf.o
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

unit_tests.exe: $(OBJPATH) $(UNITTESTSOBJS)
	$(CC) $(LFLAGS) -o unit_tests.exe $(UNITTESTSOBJS) $(LCHECKFLAGS)

$(OBJPATH)mysnprintf.o: $(SRCPATH)mysnprintf.c
	$(CC) $(CFLAGS) -o $(OBJPATH)mysnprintf.o $(SRCPATH)mysnprintf.c

$(OBJPATH)check_mysnprintf.o: $(UNITTESTSPATH)check_mysnprintf.c 
	$(CC) $(CFLAGS) -o $(OBJPATH)check_mysnprintf.o $(UNITTESTSPATH)check_mysnprintf.c

unit: $(OBJPATH)debug.lastbuildstate unit_tests.exe
	drmemory -batch -lib_blacklist "*" -- ./unit_tests.exe
	cd $(OBJPATH) && gcov  mysnprintf.o check_mysnprintf.o && cd ..

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
	rm -fv *.DS_Store
	rm -fr $(OBJPATH)
	rm -fr ./.vscode/