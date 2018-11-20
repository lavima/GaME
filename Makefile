HEADERS = $(wildcard src/*.h) \
          $(wildcard src/framework/*.h) \
          $(wildcard src/lib/*.h) \
          $(wildcard src/platform/*.h) \
          $(wildcard src/scripting/*.h) \
          $(wildcard src/simplerenderer/*.h) \
          $(wildcard src/util/*.h) 

SOURCES = $(wildcard src/*.cpp) \
          $(wildcard src/framework/*.cpp) \
          $(wildcard src/lib/*.cpp) \
          $(wildcard src/platform/*.cpp) \
          $(wildcard src/scripting/*.cpp) \
          $(wildcard src/simplerenderer/*.cpp) \
          $(wildcard src/util/*.cpp)

OBJS = $(SOURCES:.cpp=.o)

INCLUDE_DIRS = -Isrc -Iexternal_libs/pugixml-1.9 -Iexternal_libs/v8-7.0.276.31/include -Iexternal_libs/vulkan-1.1.85.0/include

CC = g++

CFLAGS = --std=c++0x

bin/GaME: $(OBJS) 

%.o: %.cpp
	$(CC) $(CFLAGS) $(INCLUDE_DIRS) -o $@ -c $<
