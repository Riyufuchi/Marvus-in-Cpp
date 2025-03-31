# Compiler and compiler flags
CXX = g++
CXXFLAGS = -Wall -Wextra -pedantic -O3 -std=c++20 `wx-config --cxxflags`
CXXLIBS = -lConsoleLib -lsqlite3 `wx-config --libs`

# ConsoleArt
SRC_DIR = src
INC_DIR = libs/ConsoleLib/src/inc
BUILD_DIR = build
LIB_DIR = libs/ConsoleLib/build

# Find all .cpp files
CPP_SRC_FILES := $(shell find $(SRC_DIR) -type f -name "*.cpp")

C_SRC_FILES := $(shell find $(SRC_DIR) -type f -name "*.c")

# Combine both .cpp and .c source files
SRC_FILES := $(CPP_SRC_FILES) $(C_SRC_FILES)

# Generate object file names
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRC_FILES))

# Application name
APP_NAME = KeoManager
APP_TARGET = $(BUILD_DIR)/$(APP_NAME)

# ConsoleLib
LIB_NAME = ConsoleLib
LIB_REPO = https://github.com/Riyufuchi/ConsoleLib.git
LIB_PATH = libs/$(LIB_NAME)

# Default target
all: $(LIB_PATH) $(APP_TARGET)

$(LIB_PATH):
	mkdir -p $(dir libs) # Ensure directory exists
	@if [ ! -d "$(LIB_PATH)" ]; then \
		git clone $(LIB_REPO) $(LIB_PATH); \
	else \
		cd $(LIB_PATH) && git pull; \
	fi
	cd $(LIB_PATH) && make

# Link executable
$(APP_TARGET): $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) -o $@ $^ -L$(LIB_DIR) -I$(INC_DIR) $(CXXLIBS)

# Compile object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -I$(INC_DIR) -c $< -o $@

# Create build directory
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Clean target
clean:
	rm -rf $(BUILD_DIR) $(APP_TARGET) $(LIB_PATH)

.PHONY: all clean

