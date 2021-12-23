CC := g++
OBJ = src/*.cpp
APPNAME := app.exe
FLAGS=-O0 -Wall -Wpedantic
DEBUG_FLAGS=-D__DEBUG__ -g

build:
	$(CC) -o $(APPNAME) $(OBJ) $(FLAGS)

debug:
	$(CC) -o $(APPNAME) $(OBJ) $(FLAGS) $(DEBUG_FLAGS)

clean:
	rm -rf *.exe *.out && cd src && rm -rf *.o *.hi *.exe *.out

run: build
	./$(APPNAME)

prof: run
	gprof ${APPNAME} gmon.out -p
