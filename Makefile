CC      = gcc
CFLAGS  = -Wall -Wextra -std=c11 -Iinclude

# build executed file
binaries/zslice: src/zslice.c src/zutils.c src/log.c include/zslice.h include/zutils.h include/log.h
	$(CC) $(CFLAGS) src/zslice.c src/zutils.c src/log.c -o binaries/zslice

# build and run
run: binaries/zslice
	./binaries/zslice

# delete builded
clean:
	rm -f binaries/zslice
