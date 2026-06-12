CC      = gcc
CFLAGS  = -Wall -Wextra -std=c11 -Iinclude

# build executed file
binaries/zslice: src/zslice.c src/zutils.c include/zslice.h include/zutils.h
	$(CC) $(CFLAGS) src/zslice.c src/zutils.c -o binaries/zslice

# build and run
run: binaries/zslice
	./binaries/zslice

# delete builded
clean:
	rm -f binaries/zslice
