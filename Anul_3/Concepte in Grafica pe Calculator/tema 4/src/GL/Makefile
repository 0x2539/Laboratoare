CC=g++ -c 
CFLAGS= -Wall -I../../include/ 
SOURCES=glew.c 
OBJECTS=

ifeq ($(OS),Windows_NT)
	LIBRARY=../../obj/Win32/glew.o
else
	LIBRARY=../../obj/Unix/glew.o
endif

all:
	$(CC) $(CFLAGS) -o $(LIBRARY) $(SOURCES) $(OBJECTS)
