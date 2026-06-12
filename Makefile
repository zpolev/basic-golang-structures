CC      = gcc
CFLAGS  = -Wall -Wextra -std=c11 -Iinclude

SRC     = $(wildcard src/*.c)        
OBJ     = $(SRC:src/%.c=binaries/%.o) 
TARGET  = binaries/zslice

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET)

binaries/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f binaries/*.o $(TARGET)

.PHONY: run clean
