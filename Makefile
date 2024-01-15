# ***
# * Copyright (C) Rodolfo Herrera Hernandez. All rights reserved.
# * Licensed under the MIT license. See LICENSE file in the project root 
# * for full license information.
# *
# * =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+
# *
# * For related information - https://github.com/rodyherrera/Lisa/
# *
# * =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
# ***

# Compiler
CXX = g++
CXXFLAGS = -std=c++2a -Wall -shared

# Include directories
INCLUDES = -I/usr/include/webkitgtk-4.0 \
           -I Dependencies/

# Linker flags
LDFLAGS = -ljavascriptcoregtk-4.0 \
          -luv \
          -lpthread \
          -lstdc++fs \
          -lboost_system \
          -lsqlite3 \
          -lPocoFoundation \
          -lPocoNet \
          -lPocoNetSSL 

# Source code directory
SOURCE_DIR = Source

# Find source files
SOURCES := $(shell find $(SOURCE_DIR) -type f -name '*.cpp')

# Object files
OBJECTS = $(SOURCES:.cpp=.o)

IS_PATH_ADDED = $(shell grep -c "$(PWD)" ~/.bashrc)

# Executable name
EXECUTABLE = Lisa

all: install_dependencies add_path build

install_dependencies:
	sudo apt-get install libwebkit2gtk-4.0-dev libboost-all-dev libsqlite3-dev libpoco-dev libuv1-dev

build: $(EXECUTABLE)

add_path:
	if [ $(IS_PATH_ADDED) -eq 0 ]; then \
        echo "export PATH=$(PWD):$$PATH" >> ~/.bashrc; \
        echo "Path added to the firmament: $(PWD)"; \
        sh ~/.bashrc; \
	else \
		echo "Path already in the firmament: $(PWD)"; \
	fi

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $^ -o $@ $(LDFLAGS)

# Clean up object files and the executable
clean:
	rm -rf $(OBJECTS) $(EXECUTABLE)