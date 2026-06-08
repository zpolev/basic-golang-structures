CC      = gcc
CFLAGS  = -Wall -Wextra -std=c11 -Iinclude

slice.o: src/slice.c include/slice.h
	$(CC) $(CFLAGS) -c src/slice.c -o slice.o
