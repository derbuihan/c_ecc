.PHONY: all clean run

CC := gcc

SRC_DIR := ./src
BUILD_DIR := ./build

SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

run: all
	./$(BUILD_DIR)/main

all: $(OBJS)
	$(CC) $(OBJS) -o $(BUILD_DIR)/main 

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) -MMD -MP -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)

-include $(OBJS:.o=.d)
