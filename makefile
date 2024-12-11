# Makefile for Gush Shell

# Compiler
CC = gcc
TARGET = gush

# Build target
all: $(TARGET)

$(TARGET): $(TARGET).c
	$(CC) -o $(TARGET) $(TARGET).c

# Clean build artifacts
clean:
	rm -f $(TARGET)

# Run the program
run: $(TARGET)
	./$(TARGET)
