CC := gcc
OBJPATH := ./out/
SRCPATH := ./src/
UNITTESTSPATH := ./unit_tests/
CFLAGS := -std=c99 --coverage -Wall -Wpedantic -Werror -Wextra -ggdb -g3 -c
LFLAGS := --coverage
LCHECKFLAGS := -lcheck -lpthread
UNITTESTSOBJS := $(OBJPATH)check_main.o $(OBJPATH)main.o
.PHONY: clean
.NOTPARALLEL: release debug

unit_tests.exe: $(OBJPATH) $(UNITTESTSOBJS)
	$(CC) $(LFLAGS) -o unit_tests.exe $(UNITTESTSOBJS) $(LCHECKFLAGS)

$(OBJPATH)main.o: $(SRCPATH)main.c
	$(CC) $(CFLAGS) -o $(OBJPATH)main.o $(SRCPATH)main.c

$(OBJPATH)check_main.o: $(UNITTESTSPATH)check_main.c 
	$(CC) $(CFLAGS) -o $(OBJPATH)check_main.o $(UNITTESTSPATH)check_main.c

unit: unit_tests.exe
	drmemory -batch -lib_blacklist "*" -- ./unit_tests.exe
	cd $(OBJPATH) && gcov main.o check_main.o && cd ..

dirs: $(INCPATH) $(OBJPATH) $(SRCPATH)

$(OBJPATH):
	mkdir $(OBJPATH)

$(SRCPATH):
	mkdir $(SRCPATH)

clean:
	rm -fv *.exe
	rm -fv *.stackdump
	rm -fv *.DS_Store
	rm -fr $(OBJPATH)
	rm -fr ./.vscode/
