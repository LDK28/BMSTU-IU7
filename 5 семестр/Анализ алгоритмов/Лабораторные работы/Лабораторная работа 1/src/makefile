CC := g++
INCPATH := ./inc/
OBJPATH := ./out/
SRCPATH := ./src/
CPPFLAGS := -I$(INCPATH) -Wall -Wpedantic -Wextra -ggdb -g3 -c
APPOBJS := $(OBJPATH)main.o $(OBJPATH)time_compare.o $(OBJPATH)manual_input.o $(OBJPATH)levenstein.o $(OBJPATH)string_gen.o $(OBJPATH)getCPUTime.o 
.PHONY: clean
.NOTPARALLEL: release debug

release: CPPFLAGS := -std=c99 -I$(INCPATH) -o -c
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

$(OBJPATH)main.o: $(SRCPATH)main.cpp
	$(CC) $(CPPFLAGS) -o $(OBJPATH)main.o $(SRCPATH)main.cpp

$(OBJPATH)time_compare.o: $(SRCPATH)time_compare.cpp
	$(CC) $(CPPFLAGS) -o $(OBJPATH)time_compare.o $(SRCPATH)time_compare.cpp

$(OBJPATH)manual_input.o: $(SRCPATH)manual_input.cpp
	$(CC) $(CPPFLAGS) -o $(OBJPATH)manual_input.o $(SRCPATH)manual_input.cpp

$(OBJPATH)levenstein.o: $(SRCPATH)levenstein.cpp
	$(CC) $(CPPFLAGS) -o $(OBJPATH)levenstein.o $(SRCPATH)levenstein.cpp

$(OBJPATH)getCPUTime.o: $(SRCPATH)getCPUTime.cpp
	$(CC) $(CPPFLAGS) -o $(OBJPATH)getCPUTime.o $(SRCPATH)getCPUTime.cpp

$(OBJPATH)string_gen.o: $(SRCPATH)string_gen.cpp
	$(CC) $(CPPFLAGS) -o $(OBJPATH)string_gen.o $(SRCPATH)string_gen.cpp

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