CC=g++
CFLAGS= -std=c++11 -w -pthread
INCLUDES = -Iinclude/
SOURCES=src/main.cpp src/loadShaders.cpp
LIBS = -Llib
LIB_SO = 

EXECUTABLE=Main
LDFLAGS += -lpthread -lSOIL -lGL -lGLU -lglut -fpermissive
OBJECTS=obj/Unix/x64/glew.o 

LBITS := $(shell getconf LONG_BIT)
ifeq ($(LBITS),64)
	OBJECTS=obj/Unix/x64/glew.o 
else
	OBJECTS=obj/Unix/x86/glew.o 
endif

all:
	$(CC) $(CFLAGS) $(INCLUDES) $(LIBS) -o $(EXECUTABLE) $(SOURCES) $(OBJECTS) $(LIB_SO) $(LDFLAGS)
