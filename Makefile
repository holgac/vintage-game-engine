CC=gcc
UNAME:=$(shell uname -s)

ifeq ($(UNAME), Darwin)
	PLATFORM=OSX
endif
ifeq ($(UNAME), Linux)
	PLATFORM=LINUX
endif

LDLIBS=-lSDL2
ifeq ($(PLATFORM), LINUX)
	LDLIBS+=-lGL -lGLU -lm
endif
ifeq ($(PLATFORM), OSX)
	LDLIBS+=-framework OpenGL
endif
LDLIBS+=-lIL -lILU -lILUT

DEBUG=true
INCLUDEDIR=./include
SRCDIR=./
CFLAGS=-c -I$(INCLUDEDIR) -Wall
OPT=-Wall
SOURCES=$(shell find $(SRCDIR) -name "*.c" | grep -Ev '_gen.c')
OBJECTS=$(SOURCES:%.c=%.o)
TARGET=vge

ifeq ($(DEBUG),true)
CFLAGS+=-g
endif

.PHONY: all
all: $(TARGET)

tests_gen.c: setup.py
		./setup.py

tests_gen.o: tests_gen.c
		$(CC) $^ $(CFLAGS) -o $@

$(TARGET): $(OBJECTS) tests_gen.o
		$(CC) $^ -o $@ $(LDLIBS)

.PHONY: clean
clean:
		rm -f $(TARGET) $(OBJECTS) tests_gen.o tests_gen.c
