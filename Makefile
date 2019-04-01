EXTERNAL_SOURCES = $(wildcard external_libs/pugixml-1.9/*.cpp)

SOURCES = $(wildcard src/*.cpp) \
          $(wildcard src/framework/*.cpp) \
          $(wildcard src/lib/*.cpp) \
          $(wildcard src/platform/*.cpp) \
          $(wildcard src/scripting/*.cpp) \
          $(wildcard src/simplerenderer/*.cpp) \
          $(wildcard src/util/*.cpp)

OBJS = $(EXTERNAL_SOURCES:.cpp=.o) $(SOURCES:.cpp=.o)

DEFINES = -D PLATFORM_GLFW_VULKAN

INCLUDE_DIRS = -Isrc -Iexternal_libs/pugixml-1.9 -Iexternal_libs/v8-7.4.256/include -Iexternal_libs/vulkan-1.1.85.0/include -Iexternal_libs/glfw-3.2.1/include
LIB_DIRS = -Lexternal_libs/v8-7.4.256/libs -Lexternal_libs/vulkan-1.1.85.0/libs -Lexternal_libs/glfw-3.2.1/libs 

LIBS = -ldl -lv8_monolith -lglfw -lvulkan

LINKER_OPTIONS = -pthread

CC = g++

CFLAGS = --std=c++17

bin/GaME: $(OBJS) 
	$(CC) -Wall -o $@ $^ $(LIBS) $(LIB_DIRS) $(LINKER_OPTIONS)

%.o: %.cpp
	$(CC) $(CFLAGS) $(DEFINES) $(INCLUDE_DIRS) -o $@ -c $<

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o
