CC := g++
INCPATH := ./inc/
OBJPATH := ./out/
SRCPATH := ./src/
CPPFLAGS := -I$(INCPATH)  -ggdb -g3 -c
APPOBJS1 := $(OBJPATH)1_fork.o
APPOBJS2 := $(OBJPATH)2_wait.o
APPOBJS3 := $(OBJPATH)3_exec.o
APPOBJSq := $(OBJPATH)qsort.o
APPOBJSs := $(OBJPATH)sum.o
APPOBJS4 := $(OBJPATH)4_pipe.o
APPOBJS5 := $(OBJPATH)5_signal.o

.PHONY: clean
.NOTPARALLEL: release debug

release: CPPFLAGS := -std=c99 -I$(INCPATH) -o -c
release: $(OBJPATH) $(OBJPATH)release.lastbuildstate app.out

debug: $(OBJPATH) $(OBJPATH)debug.lastbuildstate app.out

$(OBJPATH)debug.lastbuildstate: $(OBJPATH)
	rm -fv *.out
	rm -fv $(OBJPATH)*.o
	rm -fv $(OBJPATH)*.gcno
	rm -fv $(OBJPATH)*.gcda
	rm -fv $(OBJPATH)release.lastbuildstate
	touch $(OBJPATH)debug.lastbuildstate

$(OBJPATH)release.lastbuildstate: $(OBJPATH)
	rm -fv *.out
	rm -fv $(OBJPATH)*.o
	rm -fv $(OBJPATH)*.gcno
	rm -fv $(OBJPATH)*.gcda
	rm -fv $(OBJPATH)debug.lastbuildstate
	touch $(OBJPATH)release.lastbuildstate

1_fork.out: $(OBJPATH) $(APPOBJS1)
	$(CC) -o 1_fork.out $(APPOBJS1)

$(OBJPATH)1_fork.o: $(SRCPATH)1_fork.c
	$(CC) $(CPPFLAGS) -o $(OBJPATH)1_fork.o $(SRCPATH)1_fork.c

2_wait.out: $(OBJPATH) $(APPOBJS2)
	$(CC) -o 2_wait.out $(APPOBJS2)

$(OBJPATH)2_wait.o: $(SRCPATH)2_wait.c
	$(CC) $(CPPFLAGS) -o $(OBJPATH)2_wait.o $(SRCPATH)2_wait.c

3_exec.out: $(OBJPATH) $(APPOBJS3)
	$(CC) -o 3_exec.out $(APPOBJS3)

$(OBJPATH)3_exec.o: $(SRCPATH)3_exec.c
	$(CC) $(CPPFLAGS) -o $(OBJPATH)3_exec.o $(SRCPATH)3_exec.c

qsort.out: $(OBJPATH) $(APPOBJSq)
	$(CC) -o qsort.out $(APPOBJSq)

$(OBJPATH)qsort.o: $(SRCPATH)qsort.c
	$(CC) $(CPPFLAGS) -o $(OBJPATH)qsort.o $(SRCPATH)qsort.c

sum.out: $(OBJPATH) $(APPOBJSs)
	$(CC) -o sum.out $(APPOBJSs)

$(OBJPATH)sum.o: $(SRCPATH)sum.c
	$(CC) $(CPPFLAGS) -o $(OBJPATH)sum.o $(SRCPATH)sum.c

4_pipe.out: $(OBJPATH) $(APPOBJS4)
	$(CC) -o 4_pipe.out $(APPOBJS4)

$(OBJPATH)4_pipe.o: $(SRCPATH)4_pipe.c
	$(CC) $(CPPFLAGS) -o $(OBJPATH)4_pipe.o $(SRCPATH)4_pipe.c

5_signal.out: $(OBJPATH) $(APPOBJS5)
	$(CC) -o 5_signal.out $(APPOBJS5)

$(OBJPATH)5_signal.o: $(SRCPATH)5_signal.c
	$(CC) $(CPPFLAGS) -o $(OBJPATH)5_signal.o $(SRCPATH)5_signal.c

dirs: $(INCPATH) $(OBJPATH) $(SRCPATH)

$(OBJPATH):
	mkdir $(OBJPATH)

$(INCPATH):
	mkdir $(INCPATH)

$(SRCPATH):
	mkdir $(SRCPATH)

clean:
	rm -fv *.out
	rm -fv *.stackdump
	rm -fr $(OBJPATH)
	rm -fr ./.vscode/