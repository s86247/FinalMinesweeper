# Compiler and Flags
CC = gcc
CFLAGS = -Wall -Wextra -g
# Libraries: notcurses often requires ncurses as a dependency
LIBS = -lnotcurses -lnotcurses-core

# Target executable name
TARGET = minesweeper

# Source files (automatically includes all .c files in the directory)
SRCS = mainMineSweeper.c boardManager.c gameManager.c inputManager.c mineMananger.c

# Object files (changes .c extension to .o)
OBJS = $(SRCS:.c=.o)

# Default rule
all: $(TARGET)

# Linking the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

# Compiling source files into object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJS) $(TARGET)

# Run the program
run: $(TARGET)
	./$(TARGET)
