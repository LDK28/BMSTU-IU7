app.exe: src/strcopy.asm src/main.cpp
	mkdir -p bin
	nasm -f macho64 src/strcopy.asm -o bin/strcopy.o
	g++ -c src/main.cpp -o bin/main.o
	ld bin/main.o bin/strcopy.o -o app -macosx_version_min 11.1 -L/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/lib/ -lSystem
clean:
	rm -f app
	rm -rf bin
