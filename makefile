# Compiler and Flags
CC = gcc
CFLAGS = -Wall -Wextra -g
LIBS = -lnotcurses -lnotcurses-core

# Directory names
SRC_DIR = code
OBJ_DIR = obj

# Target executable name
TARGET = minesweeper

# List your source files (just the names)
SRCS_NAMES = mainMineSweeper.c boardManager.c gameManager.c \
             inputManager.c mineMananger.c

# Create full paths for sources (src/file.c)
SRCS = $(addprefix $(SRC_DIR)/, $(SRCS_NAMES))

# Create full paths for objects (obj/file.o)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# Default rule
all: $(OBJ_DIR) $(TARGET)

# Create the object directory if it doesn't exist
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Linking the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

# Compiling source files into the object directory
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -rf $(OBJ_DIR) $(TARGET)

# Run the program
run: $(TARGET)
	./$(TARGET)
