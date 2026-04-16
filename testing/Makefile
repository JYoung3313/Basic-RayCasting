# Name of your executable
TARGET_NAME = tester

# Directories
OBJ_DIR = obj
BIN_DIR = bin

# Final Target Path
TARGET = $(BIN_DIR)/$(TARGET_NAME)

# Compiler
CC = g++

# Compiler flags
# -Wall: show all warnings
# -g: include debugging information
# -I.: looks for header files in the current directory
CFLAGS = -Wall -g -I. $(shell pkg-config --cflags sdl2)

# Linker flags
LDFLAGS = $(shell pkg-config --libs sdl2)

# Source files
SRC = testerMain.cpp Ray.cpp

# Object files (placed inside OBJ_DIR)
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.cpp=.o))

# Default target
all: create_dirs $(TARGET)

# Create necessary directories
create_dirs:
	@mkdir -p $(OBJ_DIR) $(BIN_DIR)

# Link the executable
$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(LDFLAGS)

# Compile source files into object files
$(OBJ_DIR)/%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# Header Dependencies
# Note: We point to the files in the obj/ folder
$(OBJ_DIR)/testerMain.o: Ray.cpp Player.h Vec.h Ray.h
$(OBJ_DIR)/Ray.o: Ray.cpp Ray.h Vec.h Player.h

# Clean up build files
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Run the program
run: all
	./$(TARGET)