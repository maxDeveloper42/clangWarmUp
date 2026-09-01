CC      = gcc
CFLAGS  = -Wall -Wextra -std=c11 -pedantic
TARGET  = hashbook
SRCS    = main.c hashbook.c
OBJS    = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

%.o: %.c hashbook.h
	$(CC) $(CFLAGS) -c $< -o $@

debug: CFLAGS += -g -O0 -fsanitize=address,undefined
debug: clean $(TARGET)

valgrind: CFLAGS += -g -O0
valgrind: clean $(TARGET)

clean:
	rm -f $(OBJS) $(TARGET) 

run: $(TARGET)
	./$(TARGET)

.PHONY: all debug valgrind clean run
