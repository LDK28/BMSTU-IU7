CC=gcc
WORKDIR=src
FLAGS=-Wall -Werror -pthread

myapp.out:
	$(CC) $(FLAGS) myapp.c -o myapp.out

runmyapp: myapp.out
	./myapp.out

main.out:
	$(CC) $(FLAGS) main.c -o main.out

runmain: main.out
	./main.out

clean:
	rm *.exe *.out *.o