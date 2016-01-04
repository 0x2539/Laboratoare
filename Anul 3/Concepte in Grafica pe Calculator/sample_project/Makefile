CC=g++
CFLAGS= -std=c++11 -w
INCLUDES = -Iinclude/
SOURCES=src/main.cpp 
LIBS = 
LIB_SO = 

EXECUTABLE=Main
LDFLAGS += -lGL -lGLU -lglut
OBJECTS=obj/Unix/x64/glew.o 

LBITS := $(shell getconf LONG_BIT)
ifeq ($(LBITS),64)
	OBJECTS=obj/Unix/x64/glew.o 
else
	OBJECTS=obj/Unix/x86/glew.o 
endif

all:
	$(CC) $(CFLAGS) $(INCLUDES) $(LIBS) -o $(EXECUTABLE) $(SOURCES) $(OBJECTS) $(LIB_SO) $(LDFLAGS)
