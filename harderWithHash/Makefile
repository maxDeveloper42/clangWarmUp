CC      = gcc
CFLAGS  = -Wall -Wextra -std=c11 -pedantic
LDFLAGS =
TARGET  = hashbook
SRCS    = main.c hashbook.c
OBJS    = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)

%.o: %.c hashbook.h
	$(CC) $(CFLAGS) -c $< -o $@

# debug: add sanitizer to CFLAGS AND LDFLAGS
debug: CFLAGS += -g -O0 -fsanitize=address,undefined
debug: LDFLAGS += -fsanitize=address,undefined
debug: clean $(TARGET)

# valgrind: no sanitizer at all
valgrind: CFLAGS += -g -O0
valgrind: clean $(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all debug valgrind clean run

