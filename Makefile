CXX = g++
CXXFLAGS = -std=c++20 -Wall
INCLUDES = -I/usr/include/webkitgtk-4.0 -I Dependencies/ -I Dependencies/acl/lib_acl_cpp/include/ -I Dependencies/acl/lib_fiber/cpp/include/
LDFLAGS = -ljavascriptcoregtk-4.0 -luv -lpthread -lstdc++fs -L/home/idorherz/Desktop/Development/Lisa/Dependencies/acl/build/lib/ -lacl_cpp -lacl -lfiber_cpp -lfiber -lprotocol -lz
SOURCE_DIR = Source
SOURCES := $(shell find $(SOURCE_DIR) -type f -name '*.cpp')
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = Lisa

all: $(EXECUTABLE)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $^ -o $@ $(LDFLAGS)

clean:
	rm -rf $(OBJECTS) $(EXECUTABLE)
