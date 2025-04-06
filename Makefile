CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
TARGET = 3cube_solver
SRC = 3cube_solver.cpp

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm -f $(TARGET)