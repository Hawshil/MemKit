CXX = g++
CXXFLAGS = -std=c++23 -Wall -Wextra -Wpedantic -g -Iinclude

SRC_DIR = src
BUILD_DIR = build

TARGET = $(BUILD_DIR)/allocator

SRCS = \
       $(SRC_DIR)/main.cpp \
       $(SRC_DIR)/memalloc.cpp

OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(OBJS) -o $(TARGET)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@


run: all
	./$(TARGET)

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all run clean


