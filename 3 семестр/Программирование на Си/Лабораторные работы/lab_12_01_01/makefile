CC := gcc
INCPATH := ./inc/
OBJPATH := ./out/
SRCPATH := ./src/
FUNCTESTSPATH := ./func_tests/
UNITTESTSPATH := ./unit_tests/
CFLAGS := -std=c99 -Wall -Wpedantic -Wextra
LFLAGS := --coverage
LCHECKFLAGS := -lcheck -lpthread
APPOBJS := $(OBJPATH)main.o $(OBJPATH)static_lib
UNITTESTSOBJS := $(OBJPATH)check_main.o $(OBJPATH)check_lib.o $(OBJPATH)static_lib.o
.PHONY: clean
.NOTPARALLEL: release debug

release: CFLAGS := -std=c99 -I$(INCPATH) -o2 -c
release: LFLAGS := -o2
release: $(OBJPATH) $(OBJPATH)release.lastbuildstate static

debug: $(OBJPATH) $(OBJPATH)debug.lastbuildstate static

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


static: $(OBJPATH) $(SRCPATH)static_main.c $(OBJPATH)staticlib.a
	$(CC) $(CFLAGS) $(SRCPATH)static_main.c $(OBJPATH)staticlib.a -o app.exe

$(OBJPATH)staticlib.a: $(OBJPATH)static_lib.o
	ar rc $(OBJPATH)staticlib.a $(OBJPATH)static_lib.o	

$(OBJPATH)static_lib.o: $(SRCPATH)static_lib.c
	$(CC) $(CFLAGS) -c $(SRCPATH)static_lib.c -o $(OBJPATH)static_lib.o


dynamic_link: $(OBJPATH) $(OBJPATH)dynamic_link_main.o dynamiclib.dll
	$(CC) $(OBJPATH)dynamic_link_main.o dynamiclib.dll -o app.exe

$(OBJPATH)dynamic_link_main.o: $(SRCPATH)dynamic_link_main.c
	$(CC) $(CFLAGS) -c $(SRCPATH)dynamic_link_main.c -o $(OBJPATH)dynamic_link_main.o

dynamiclib.dll: $(OBJPATH)dynamic_lib.o
	$(CC) -shared $(OBJPATH)dynamic_lib.o -Wl,--subsystem,windows -o dynamiclib.dll

$(OBJPATH)dynamic_lib.o:
	$(CC) $(CFLAGS) -D ARR_EXPORTS -c $(SRCPATH)dynamic_lib.c -o $(OBJPATH)dynamic_lib.o


dynamic_load: $(OBJPATH) dynamiclib.dll
	$(CC) $(CFLAGS) $(SRCPATH)dynamic_load_main.c -o app.exe


func: $(OBJPATH)debug.lastbuildstate static
	@echo
	cd $(FUNCTESTSPATH) && cmd //C all_test.cmd


unit: $(OBJPATH)debug.lastbuildstate unit_tests_static.exe unit_tests_dynamic.exe
	drmemory -batch -lib_blacklist "*" -- ./unit_tests_static.exe
	cd $(OBJPATH) && gcov check_static.o static_lib.o && cd ..
	drmemory -batch -lib_blacklist "*" -- ./unit_tests_dynamic.exe
	cd $(OBJPATH) && gcov check_static.o static_lib.o && cd ..

unit_tests_static.exe: $(OBJPATH) $(UNITTESTSOBJS)
	$(CC) $(LFLAGS) -o unit_tests_static.exe $(UNITTESTSOBJS) $(LCHECKFLAGS)

$(OBJPATH)check_main.o: $(UNITTESTSPATH)check_main.c
	$(CC) $(CFLAGS) $(CFLAGS) -o $(OBJPATH)check_main.o $(UNITTESTSPATH)check_main.c

$(OBJPATH)check_static.o: $(UNITTESTSPATH)check_static.c
	$(CC) $(CFLAGS) $(CFLAGS) -o $(OBJPATH)check_static.o $(UNITTESTSPATH)check_static.c

unit_tests_dynamic: $(OBJPATH) $(OBJPATH)check_dynamic.o dynamiclib.dll
	$(CC) $(OBJPATH)check_dynamic.o dynamiclib.dll -o unit_tests_dynamic.exe $(LCHECKFLAGS)

$(OBJPATH)check_dynamic.o: $(UNITTESTSPATH)check_dynamic.c
	$(CC) $(CFLAGS) $(LFLAGS) -c $(UNITTESTSPATH)check_dynamic.c -o $(OBJPATH)check_dynamic.o


dirs: $(INCPATH) $(OBJPATH) $(SRCPATH) $(UNITTESTSOBJS)

$(STATICPATH)$(OBJPATH):
	mkdir $(STATICPATH)$(OBJPATH)

$(INCPATH):
	mkdir $(INCPATH)

$(SRCPATH):
	mkdir $(SRCPATH)


clean:
	rm -fv *.exe
	rm -fv *.stackdump
	rm -fv *.dll
	rm -fr $(OBJPATH)
	rm -fr *.vscode