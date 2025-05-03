# Compiler
CXX = g++
# Compiler flags
CXXFLAGS = -Wall -g
# Include paths (add -I flags for header directories if needed)
INCLUDES = -I.
# Target executable
TARGET = main
# For deleting the target
TARGET_DEL = main.out

# Find all source files recursively
SRCS := $(shell find . -name "*.cpp")
# Generate object file paths (preserving directory structure)
OBJS := $(SRCS:.cpp=.o)
# Find all header files recursively (for dependency generation)
HEADERS := $(shell find . -name "*.h" -o -name "*.hpp")

# Default rule to build and run the executable
all: $(TARGET) run

# Rule to link object files into the target executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Rule to compile .cpp files into .o files with automatic header dependencies
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -MMD -MP -c $< -o $@

# Include dependency files
-include $(OBJS:.o=.d)

# Rule to run the executable
run: $(TARGET)
	./$(TARGET)

# Clean rule to remove generated files
clean:
	del $(TARGET_DEL) $(OBJS) $(OBJS:.o=.d)