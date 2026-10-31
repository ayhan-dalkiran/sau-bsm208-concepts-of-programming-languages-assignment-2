# Directories
SRC_DIR := src
INC_DIR := include
OBJ_DIR := lib
BIN_DIR := bin

# Compiler and flags
CC := gcc
CFLAGS := -I $(INC_DIR) -std=c90 -Wall -Wextra -Werror -pedantic -pedantic-errors

# Source and object files
SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

# Executable name
TARGET := $(BIN_DIR)/pdp2.exe

# Default target
all: $(TARGET) run

# Link object files to create the executable
$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CC) $(OBJS) -o $@

# Compile source files into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

run:
	$(TARGET)

.PHONY: all run
