CC := gcc
INCPATH := ./inc/
OBJPATH := ./out/
SRCPATH := ./src/
CFLAGS := -std=c99 -Wall -Werror -Wpedantic -Wextra
APPOBJS := $(OBJPATH)fibonacci.o                
.PHONY: clean
.NOTPARALLEL: release debug

release: CFLAGS := -std=c99 -I$(INCPATH) -o2 -c
release: LFLAGS:=-o2 fibonacci.dll
release: $(OBJPATH) $(OBJPATH)release.lastbuildstate fibonacci.dll main.py
	python3 main.py

app.exe: $(OBJPATH) $(APPOBJS) fibonacci.dll main.py
	python3 main.py

fibonacci.dll: $(OBJPATH) $(OBJPATH)fibonacci.o 
	$(CC) -shared $(OBJPATH)fibonacci.o -Wl,--subsystem,windows -o fibonacci.dll 

$(OBJPATH)fibonacci.o: $(SRCPATH)fibonacci.c $(INCPATH)fibonacci.h
	$(CC) $(CFLAGS) -c $(SRCPATH)fibonacci.c -o $(OBJPATH)fibonacci.o

debug: $(OBJPATH) $(OBJPATH)debug.lastbuildstate fibonacci.dll main.py
	python3 main.py

$(OBJPATH)debug.lastbuildstate: $(OBJPATH)
	rm -fv *.exe
	rm -fv $(OBJPATH)*.o
	rm -fv $(OBJPATH)*.gcno
	rm -fv $(OBJPATH)*.gcda
	rm -fr $(OBJPATH)*.dll
	rm -fv $(OBJPATH)release.lastbuildstate
	touch $(OBJPATH)debug.lastbuildstate

$(OBJPATH)release.lastbuildstate: $(OBJPATH)
	rm -fv *.exe
	rm -fv $(OBJPATH)*.o
	rm -fv $(OBJPATH)*.gcno
	rm -fv $(OBJPATH)*.gcda
	rm -fr $(OBJPATH)*.dll
	rm -fv $(OBJPATH)debug.lastbuildstate
	touch $(OBJPATH)release.lastbuildstate


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
	rm -fv *.dll
	rm -fr *.vscode
	rm -fr $(OBJPATH)