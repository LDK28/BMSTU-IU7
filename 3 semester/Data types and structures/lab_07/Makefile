C = gcc
LINTER = CodeChecker

TARGET = app.exe
LIBRIES = 
CFLAGS = -Wall -std=gnu11 -O0

SRCS = \
src/main.c \
src/io.c \
src/utils.c \
src/matrix.c \
src/graph.c

.PHONY: clean

app.exe: $(SRCS)
	$(CC) -o $(TARGET) $(CFLAGS) $(SRCS) -g -ggdb $(CFLAGS) $(LIBRIES) -I.

clean:
	rm -rf $(TARGET) *.gcov *.gcda *.gcno *.exe temp.png temp.txt *.dSYM
