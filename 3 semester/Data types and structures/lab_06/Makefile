C = gcc
LINTER = CodeChecker

TARGET = app.exe
LIBRIES = 
CFLAGS = -Wall -std=gnu11 -O0

SRCS = \
src/main.c \
src/io.c \
src/utils.c \
src/hash_table.c \
src/btree.c \
src/avl_tree.c \
src/hash_funcs.c \
src/analize.c

.PHONY: clean

app.out: $(SRCS)
	$(CC) -o $(TARGET) $(CFLAGS) $(SRCS) -g -ggdb $(CFLAGS) $(LIBRIES) -I.

clean:
	rm -rf $(TARGET) *.gcov *.gcda *.gcno *.exe
