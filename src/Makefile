CC=gcc
INCLUDEDIR=../include
CFLAGS=-c -I$(INCLUDEDIR) -Wall

SOURCES=$(shell find $(SRCDIR) -name "*.c")
DEPFILES:=$(patsubst %.c,%.d,$(SOURCES))
OBJECTS:=$(patsubst %.c,%.o,$(SOURCES))

#Don't create dependencies for these goals
NODEPS:=clean
ifeq (0, $(words $(findstring $(MAKECMDGOALS), $(NODEPS))))
	-include $(DEPFILES)
endif
TARGET=libvge.a
.DEFAULT_GOAL := $(TARGET)

.PHONY: all
all: $(TARGET)

%.d: %.c
	$(CC) $(CFLAGS) -MM -MT  $(patsubst %.c,%.o,$<) $< -MF $@

#This rule does the compilation
%.o: %.c %.d %.h
	@$(MKDIR) $(dir $@)
	$(CC) $(CFLAGS) -o $@ -c $<

$(TARGET): $(OBJECTS)
	ar rcs $(TARGET) $(OBJECTS)

.PHONY: clean
clean:
		rm -f $(TARGET) $(OBJECTS) $(DEPFILES)
