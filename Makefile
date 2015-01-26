CC=gcc

DEBUG=false
INCLUDEDIR=./include
SRCDIR=./
CFLAGS=-c -I$(INCLUDEDIR) -g
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
		$(CC) $^ -o $@

.PHONY: clean
clean:
		rm -f $(TARGET) $(OBJECTS)
