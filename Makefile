CC ?= gcc
CFLAGS ?= -O3 -std=c99 -Wall -Wextra -pedantic
TARGET = gxnox_tool

all: $(TARGET)

$(TARGET): gxnox_tool.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(TARGET) $(TARGET).exe *.o

.PHONY: all clean
