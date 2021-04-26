CC := gcc
INCPATH := ./inc/
OBJPATH := ./out/
SRCPATH := ./src/
FUNCTESTSPATH := ./func_tests/
CFLAGS := -std=c99 --coverage -I$(INCPATH) -Wall -Wpedantic -Werror -Wextra -ggdb -g3 -c
LFLAGS := --coverage
LCHECKFLAGS := -lcheck -lpthread
APPOBJS := $(OBJPATH)main.o $(OBJPATH)array.o
.PHONY: clean check

build: $(OBJPATH) $(APPOBJS)
	$(CC) $(LFLAGS) -o app.exe $(APPOBJS)

$(OBJPATH)array.o: $(SRCPATH)array.c
	$(CC) $(CFLAGS) -o $(OBJPATH)array.o $(SRCPATH)array.c

$(OBJPATH)main.o: $(SRCPATH)main.c
	$(CC) $(CFLAGS) -o $(OBJPATH)main.o $(SRCPATH)main.c

check:
	cppcheck $(SRCPATH)main.c $(SRCPATH)array.c

func: app.exe
	@echo
	cd $(FUNCTESTSPATH) && cmd //C all_test.cmd
	@echo
	gcov -n $(OBJPATH)main.o
	gcov -n $(OBJPATH)array.o

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
	rm -fr *.dSYM
	rm -fr $(OBJPATH)
	rm -fr ./.vscode/