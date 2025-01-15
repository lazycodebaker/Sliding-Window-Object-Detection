# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++17 $(shell pkg-config --cflags opencv4)

# Linker flags
LDFLAGS = $(shell pkg-config --libs opencv4)

# Include and library paths (adjust as per your system)
INCLUDE_DIRS = -I/opt/homebrew/Cellar/opencv/4.10.0_11/include/opencv4
LIB_DIRS = -L/opt/homebrew/Cellar/opencv/4.10.0_11/lib

# Output binary
TARGET = main

# Source file
SRC = sliding_window.cpp

# Build the binary
all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(INCLUDE_DIRS) $(SRC) -o $(TARGET) $(LIB_DIRS) $(LDFLAGS)

# Clean build files
clean:
	rm -f $(TARGET)
