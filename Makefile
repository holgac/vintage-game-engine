CC=gcc

LDLIBS = -lSDL2 -framework OpenGL

DEBUG=true
INCLUDEDIR=./include
SRCDIR=./
CFLAGS=-c -I$(INCLUDEDIR) -Wall -pedantic-errors
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
		$(CC) $^ -o $@ $(LDLIBS)

.PHONY: clean
clean:
		rm -f $(TARGET) $(OBJECTS)
