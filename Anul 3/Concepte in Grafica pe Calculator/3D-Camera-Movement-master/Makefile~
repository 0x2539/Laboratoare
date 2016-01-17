CC=g++

WARNING_FLAGS=-Wall -Wextra -Weffc++ -Winit-self -Wmissing-include-dirs -Wswitch-default -Wswitch-enum -Wunused-parameter -Wstrict-overflow=5 -Wfloat-equal -Wshadow -Wc++0x-compat -Wconversion -Wsign-conversion -Wmissing-declarations -Wstrict-null-sentinel -Woverloaded-virtual -Wsign-promo -Werror -pedantic
FORMATTING_FLAGS=-fno-pretty-templates -fmessage-length=80 -fdiagnostics-show-option
CFLAGS=${WARNING_FLAGS} ${FORMATTING_FLAGS} -g -std=c++0x -pipe  -frepo
INCLUDES = -Iinclude/

LDFLAGS=
LDLIBS=-lGL -lglut -lGLU -lX11 -lm -lGLEW

TARGET=main
OBJECTS=$(addsuffix .o, $(basename $(shell ls *.C | grep -v Test)))
HEADERS=$(addsuffix .h, $(basename $(shell ls *.h | grep -v Test)))

TEST_LDFLAGS=-lboost_unit_test_framework
TEST_LDLIBS=${LDLIBS}
TEST_TARGET=test
TEST_OBJECTS=$(addsuffix .o, $(basename $(shell ls *.C | grep -v main)))

CLEAN_TARGETS=$(addsuffix .o, $(basename $(shell ls *.C))) ${TARGET} ${TEST_TARGET} *.rpo *.gch makefile.dep

STUDENT_NUMBER=memo
TASK=practical
NUMBER=1

all: ${OBJECTS} 
	${CC} $(INCLUDES) ${LDFLAGS} ${LDLIBS} $^ -o ${TARGET}

test: ${TEST_OBJECTS}
	${CC} $(INCLUDES) ${TEST_LDFLAGS} ${TEST_LDLIBS} $^ -o ${TEST_TARGET}

%.o:
	${CC} $(INCLUDES) ${CFLAGS} -c ${LDFLAGS} $< -o $@

# We override Test.o's compilation so it doesn't use the CFLAGS, this is because
# boost uses coding practices that would cause problems with them.
Test.o: Test.C Makefile
	${CC} -c $< -o $@

clean:
	rm ${CLEAN_TARGETS}

tar:
	make clean; tar -cvjf ${STUDENT_NUMBER}_${TASK}_${NUMBER}.tar.bz2 *

# Calculate dependencies based on output from gcc -MM.
makefile.dep: *.[Ch]
	for i in *.C; do gcc -MM "$${i}"; done > $@
include makefile.dep
