CC = gcc
CFLAGS = -Wall -Wextra -g
LIBS = -lnotcurses -lnotcurses-core -lm

SRC_DIR = code
OBJ_DIR = obj

TARGET = minesweeper

SRCS_NAMES = mainMineSweeper.c boardManager.c gameManager.c \
             inputManager.c tileMananger.c logicManager.c

SRCS = $(addprefix $(SRC_DIR)/, $(SRCS_NAMES))

OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

all: $(OBJ_DIR) $(TARGET)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LIBS) 

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(TARGET)

run: $(TARGET)
	./$(TARGET)
