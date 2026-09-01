CC      = gcc
CFLAGS  = -Wall -Wextra -std=c11 -pedantic
TARGET  = phonebook
SRCS    = main.c phonebook.c
OBJS    = $(SRCS:.c=.o)

# Default: release build
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

%.o: %.c phonebook.h
	$(CC) $(CFLAGS) -c $< -o $@

# Debug build: includes symbols, no optimization, sanitizers
debug: CFLAGS += -g -O0 -fsanitize=address,undefined
debug: clean $(TARGET)

# Valgrind-friendly debug (no sanitizers, pure symbols)
valgrind: CFLAGS += -g -O0
valgrind: clean $(TARGET)

clean:
	rm -f $(OBJS) $(TARGET) 

# Quick run after build
run: $(TARGET)
	./$(TARGET)

.PHONY: all debug valgrind clean run
