# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -I/usr/include/eigen3 -I.

# Output executable name
TARGET = seamcarving

# Source file
SRC = proj_6.cpp

# Build rule
$(TARGET): $(SRC)
	$(CXX) -o $(TARGET) $(SRC) $(CXXFLAGS)

# Clean rule
.PHONY: clean
clean:
	rm -f $(TARGET)
