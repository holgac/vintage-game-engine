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
	LDLIBS+=-lGL
endif
ifeq ($(PLATFORM), OSX)
	LDLIBS+=-framework OpenGL
endif

DEBUG=true
INCLUDEDIR=./include
SRCDIR=./
CFLAGS=-c -I$(INCLUDEDIR) -Wall -g
OPT=-Wall
SOURCES=$(shell find $(SRCDIR) -name "*.c")
OBJECTS=$(SOURCES:%.c=%.o)
TARGET=vge

ifeq ($(DEBUG),true)
CFLAGS+=-g
endif

.PHONY: all
all: $(TARGET)

$(TARGET): $(OBJECTS)
		./setup.py
		$(CC) $^ -o $@ $(LDLIBS)

.PHONY: clean
clean:
		rm -f $(TARGET) $(OBJECTS)
