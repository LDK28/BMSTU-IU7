CC := gcc
INCPATH := ./inc/
OBJPATH := ./out/
SRCPATH := ./src/
UNITTESTSPATH := ./unit_tests/
CFLAGS := -std=c99 --coverage -I$(INCPATH) -Wall -Wpedantic -Werror -Wextra -ggdb -g3 -c
LFLAGS := --coverage
LCHECKFLAGS := -lcheck -lpthread
UNITTESTSOBJS := $(OBJPATH)check_main.o $(OBJPATH)check_list.o $(OBJPATH)list.o
.PHONY: clean
.NOTPARALLEL: release debug

unit_tests.exe: $(OBJPATH) $(UNITTESTSOBJS)
	$(CC) $(LFLAGS) -o unit_tests.exe $(UNITTESTSOBJS) $(LCHECKFLAGS)

$(OBJPATH)list.o: $(SRCPATH)list.c
	$(CC) $(CFLAGS) -o $(OBJPATH)list.o $(SRCPATH)list.c

$(OBJPATH)check_main.o: $(UNITTESTSPATH)check_main.c 
	$(CC) $(CFLAGS) -o $(OBJPATH)check_main.o $(UNITTESTSPATH)check_main.c

$(OBJPATH)check_list.o: $(UNITTESTSPATH)check_list.c 
	$(CC) $(CFLAGS) -o $(OBJPATH)check_list.o $(UNITTESTSPATH)check_list.c 

unit: unit_tests.exe
	drmemory -batch -lib_blacklist "*" -- ./unit_tests.exe
	cd $(OBJPATH) && gcov list.o check_list.o && cd ..

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