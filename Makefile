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

CC = g++

CFLAGS = '--std=c++0x'

bin/GaME: $(OBJS) 

%.o: %.cpp
	$(CC) $(CFLAGS) -o $@ -c $<
