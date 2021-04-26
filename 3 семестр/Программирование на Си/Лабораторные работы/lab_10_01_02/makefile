CC := gcc
INCPATH := ./inc/
OBJPATH := ./out/
SRCPATH := ./src/
FUNCTESTSPATH := ./func_tests/
UNITTESTSPATH := ./unit_tests/
CFLAGS := -std=c99 --coverage -I$(INCPATH) -Wall -Wpedantic -Werror -Wextra -ggdb -g3 -c
LFLAGS := --coverage
LCHECKFLAGS := -lcheck -lpthread
APPOBJS := $(OBJPATH)main.o $(OBJPATH)polinom.o
UNITTESTSOBJS := $(OBJPATH)check_polinom.o $(OBJPATH)polinom.o
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

$(OBJPATH)polinom.o: $(SRCPATH)polinom.c
	$(CC) $(CFLAGS) -o $(OBJPATH)polinom.o $(SRCPATH)polinom.c

$(OBJPATH)main.o: $(SRCPATH)main.c
	$(CC) $(CFLAGS) -o $(OBJPATH)main.o $(SRCPATH)main.c

$(OBJPATH)check_polinom.o: $(UNITTESTSPATH)check_polinom.c 
	$(CC) $(CFLAGS) -o $(OBJPATH)check_polinom.o $(UNITTESTSPATH)check_polinom.c 

unit: $(OBJPATH)debug.lastbuildstate unit_tests.exe
	drmemory -batch -lib_blacklist "*" s-- ./unit_tests.exe
	cd $(OBJPATH) && gcov polinom.o check_polinom.o && cd ..

func: $(OBJPATH)debug.lastbuildstate app.exe
	@echo
	cd $(FUNCTESTSPATH) && cmd //C all_test.cmd
	@echo
	gcov -n $(OBJPATH)main.o
	gcov -n $(OBJPATH)polinom.o

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