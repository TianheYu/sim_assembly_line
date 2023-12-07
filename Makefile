# Makefile for assembly_line project

# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++11

# Source files
SRCS = main.cpp assembly_line.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Header files
HEADERS = assembly_line.h

# Target executable
TARGET = assembly_line

# Build rule for the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Build rule for object files
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Phony target to clean up files
.PHONY: clean
clean:
	rm -f $(OBJS) $(TARGET)
