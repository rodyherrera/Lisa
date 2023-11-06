CXX = g++
CXXFLAGS = -std=c++23 -Wall
INCLUDES = -I/usr/include/webkitgtk-4.0 -I Dependencies/ -I Dependencies/infoware/include/  -I Dependencies/sqlite3pp/headeronly_src/
LDFLAGS = -ljavascriptcoregtk-4.0 -luv -lpthread -lstdc++fs -LDependencies/infoware/build/lib/ -linfoware -lboost_system -lsqlite3
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
