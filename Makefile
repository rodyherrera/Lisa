# Compiler
CXX = g++
CXXFLAGS = -std=c++23 -Wall -shared

# Include directories
INCLUDES = -I/usr/include/webkitgtk-4.0 \
           -I Dependencies/ \
           -I Dependencies/infoware/include/ \
           -I Dependencies/sqlite3pp/headeronly_src/

# Linker flags
LDFLAGS = -ljavascriptcoregtk-4.0 \
          -luv \
          -lpthread \
          -lstdc++fs \
          -LDependencies/infoware/build/lib/ \
          -linfoware \
          -lboost_system \
          -lsqlite3

# Source code directory
SOURCE_DIR = Source

# Find source files
SOURCES := $(shell find $(SOURCE_DIR) -type f -name '*.cpp')

# Object files
OBJECTS = $(SOURCES:.cpp=.o)

# Executable name
EXECUTABLE = Lisa

# Build the executable
all: $(EXECUTABLE)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $^ -o $@ $(LDFLAGS)

# Clean up object files and the executable
clean:
	rm -rf $(OBJECTS) $(EXECUTABLE)
