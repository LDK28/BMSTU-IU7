CC=gcc
FLAGS=-Wall

TRASH=*.o *.exe

app.exe: main.o mtx.o
	$(CC) $(FLAGS) $^ -o $@
	
main.o: main.c
	$(CC) $(FLAGS) $< -c
	
mtx.o: mtx.c
	$(CC) $(FLAGS) $< -c	
	
clean: 
	rm -f $(TRASH)
