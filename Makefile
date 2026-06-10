CC = gcc
CFLAGS = -Wall -g -lm
TARGET = graphics_editor

# Default target
all: $(TARGET)

# Compile the program
$(TARGET): main.c
	$(CC) $(CFLAGS) -o $(TARGET) main.c -lm

# Run the program
run: $(TARGET)
	./$(TARGET)

# Clean build artifacts
clean:
	rm -f $(TARGET) *.o

# Help
help:
	@echo "Usage: make [target]"
	@echo "  all   - Build the graphics editor (default)"
	@echo "  run   - Build and run the graphics editor"
	@echo "  clean - Remove build artifacts"
	@echo "  help  - Show this help message"

.PHONY: all run clean help
