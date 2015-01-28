CC=gcc

LDLIBS = -lSDL2 -framework OpenGL

DEBUG=false
INCLUDEDIR=./include
SRCDIR=./
CFLAGS=-c -I$(INCLUDEDIR) -g -Wall
OPT=-Wall
SOURCES=$(shell find $(SRCDIR) -name "*.c")
OBJECTS=$(SOURCES:%.c=%.o)
TARGET=vge

ifneq ($(DEBUG),false)
OPT+=-g
endif

.PHONY: all
all: $(TARGET)

$(TARGET): $(OBJECTS)
		$(CC) $^ -o $@ $(LDLIBS)

.PHONY: clean
clean:
		rm -f $(TARGET) $(OBJECTS)
