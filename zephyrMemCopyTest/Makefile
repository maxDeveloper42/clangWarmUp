# Makefile for my_memcpy testing.
#
# Two build configurations:
#   - default (speed):  word‑optimised copy (macro NOT defined)
#   - size_opt:         byte‑only copy (macro IS defined)
#
# Usage:
#   make          # builds and runs the default (speed) version
#   make size_opt # builds and runs the size‑optimised version
#   make clean    # remove binaries

CC       = gcc
CFLAGS   = -std=gnu99 -Wall -Wextra -O2 -g
LDFLAGS  =
SOURCES  = memcpy.c test_memcpy.c
OBJS     = $(SOURCES:.c=.o)
TARGET   = test_memcpy
TARGET_SZ = test_memcpy_small

.PHONY: all clean size_opt

all: $(TARGET)
	./$(TARGET)

size_opt: CFLAGS += -DCONFIG_MINIMAL_LIBC_OPTIMIZE_STRING_FOR_SIZE
size_opt: $(TARGET_SZ)
	./$(TARGET_SZ)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(TARGET_SZ): $(SOURCES)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c memcpy.h
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS) $(TARGET) $(TARGET_SZ)
