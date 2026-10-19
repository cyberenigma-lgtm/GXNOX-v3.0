CC = gcc
CFLAGS = -O3 -Wall -Wextra -std=c99 -Isrc
LDFLAGS = -lpsapi

SRC = src/gxnox_core.c src/dual_parity.c src/neurocobol_rules.c src/main.c
TARGET = bin/gxnox_tool

all: $(TARGET)

$(TARGET): $(SRC)
	@mkdir -p bin
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) $(LDFLAGS)

clean:
	rm -rf bin/*.exe bin/gxnox_tool *.o

test: all
	./$(TARGET) inspect D:/BOVEDA_DOCUMENTACION_GXNOX.gxnox
