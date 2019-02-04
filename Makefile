SOURCES = $(wildcard src/*.cpp) \
          $(wildcard src/framework/*.cpp) \
          $(wildcard src/lib/*.cpp) \
          $(wildcard src/platform/*.cpp) \
          $(wildcard src/scripting/*.cpp) \
          $(wildcard src/simplerenderer/*.cpp) \
          $(wildcard src/util/*.cpp)

OBJS = $(SOURCES:.cpp=.o)

DEFINES = -D PLATFORM_GLFW_VULKAN

INCLUDE_DIRS = -Isrc -Iexternal_libs/pugixml-1.9 -Iexternal_libs/v8-7.0.276.31/include -Iexternal_libs/vulkan-1.1.85.0/include -Iexternal_libs/glfw-3.2.1/include

CC = g++

CFLAGS = --std=c++17

bin/GaME: $(OBJS) 

%.o: %.cpp
	$(CC) $(CFLAGS) $(DEFINES) $(INCLUDE_DIRS) -o $@ -c $<
