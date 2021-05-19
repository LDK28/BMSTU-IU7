app.exe: main.c
	gcc -S -masm=intel main.c
	gcc  -m80387 -c main.c -o main.o
	ld main.o -o app -macosx_version_min 11.1 -L/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/lib/ -lSystem
	
clean:
	rm -f app main.o main.s

