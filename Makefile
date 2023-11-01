CXX = g++
CXXFLAGS = -std=c++20 -Wall
INCLUDES = -I/usr/include/webkitgtk-4.0 -I Dependencies/
LDFLAGS = -ljavascriptcoregtk-4.0 -luv -lpthread -lstdc++fs
SOURCE_DIR = Source
SOURCES := $(shell find $(SOURCE_DIR) -type f -name '*.cpp')
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = Lisa

all: $(EXECUTABLE)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Regla para enlazar objetos y crear el ejecutable
$(EXECUTABLE): $(OBJECTS)
	$(CXX) $^ -o $@ $(LDFLAGS)

# Limpieza de archivos generados
clean:
	rm -rf $(OBJECTS) $(EXECUTABLE)
