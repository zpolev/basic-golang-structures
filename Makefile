CC        = gcc
CFLAGS    = -Wall -Wextra -Wpedantic -std=c11 -g -Iinclude
FSANITIZE = -fsanitize=address,undefined

SRC      = $(wildcard src/*.c)
OBJ      = $(SRC:src/%.c=binaries/%.o)
TARGET   = binaries/zslice

LIB_SRC  = $(filter-out src/main.c,$(SRC))   
TEST_SRC = $(wildcard tests/*.c)
TEST_BIN = binaries/slice-test

$(TARGET): $(OBJ) | binaries
	$(CC) $(CFLAGS) $(OBJ) -o $@

binaries/%.o: src/%.c | binaries
	$(CC) $(CFLAGS) -c $< -o $@

binaries:                 
	mkdir -p binaries

run: $(TARGET)
	./$(TARGET)

sanitize: $(SRC) | binaries
	$(CC) $(CFLAGS) $(FSANITIZE) $(SRC) -o $(TARGET)
	./$(TARGET)

test: $(TEST_SRC) $(LIB_SRC) | binaries
	$(CC) $(CFLAGS) $(FSANITIZE) $(TEST_SRC) $(LIB_SRC) -o $(TEST_BIN)
	./$(TEST_BIN)

clean:
	rm -f binaries/*.o $(TARGET) $(TEST_BIN)

.PHONY: run clean sanitize test
