CC=gcc
CFLAGS=-Wall -Wextra
LDFLAGS=

IDIR=include
CFLAGS += -I $(IDIR)

SRC_DIR=src
BUILD_DIR=build
BIN_DIR=bin

SRC=$(wildcard $(SRC_DIR)/*.c)
OBJ=$(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC))
TARGET=$(BIN_DIR)/cshell

all: $(TARGET)

$(TARGET): $(OBJ) | $(BIN_DIR)
	$(CC) -o $(TARGET) $(CFLAGS) $(LDFLAGS) $(OBJ)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) -c -o $@ $< $(CFLAGS) $(LDFLAGS)

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

$(BIN_DIR):
	@mkdir -p $(BIN_DIR)

.PHONY: clean run dev

dev: all run

run:
	@$(TARGET)

clean:
	@rm -rf ./$(BUILD_DIR) ./$(BIN_DIR)
