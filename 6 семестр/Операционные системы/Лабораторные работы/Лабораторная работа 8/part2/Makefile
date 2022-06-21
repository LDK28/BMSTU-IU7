CC = gcc

.PHONY: all 
all: server.out client.out

%.out: %.c
	$(CC) -o $@ $^

clean:
	rm -rf *.out
