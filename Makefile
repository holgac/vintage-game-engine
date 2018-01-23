DEBUG=true
CC=gcc
UNAME:=$(shell uname -s)

ifeq ($(UNAME), Darwin)
	PLATFORM=OSX
endif
ifeq ($(UNAME), Linux)
	PLATFORM=LINUX
endif

LDLIBS=-lSDL2 -lIL -lILU -lILUT
ifeq ($(PLATFORM), LINUX)
	LDLIBS+=-lGL -lGLU -lm
endif
ifeq ($(PLATFORM), OSX)
	LDLIBS+=-framework OpenGL
endif

INCLUDEDIR=./include

CFLAGS=-c -I$(INCLUDEDIR) -Wall

ifeq ($(DEBUG),true)
CFLAGS+=-g
endif

SRCDIR=./src
SOURCES=$(shell find $(SRCDIR) -name "*.c")
DEPFILES:=$(patsubst %.c,%.d,$(SOURCES))
OBJECTS:=$(patsubst %.c,%.o,$(SOURCES))

TEST_SRCDIR=./tests
TEST_SOURCES=$(shell find $(TEST_SRCDIR) -name "*.c")
TEST_DEPFILES:=$(patsubst %.c,%.d,$(TEST_SOURCES))
TEST_OBJECTS:=$(patsubst %.c,%.o,$(TEST_SOURCES))

#Don't create dependencies for these goals
NODEPS:=clean
ifeq (0, $(words $(findstring $(MAKECMDGOALS), $(NODEPS))))
	-include $(DEPFILES)
endif
.DEFAULT_GOAL := libvge.a

%.d: %.c
	$(CC) $(CFLAGS) -MM -MT  $(patsubst %.c,%.o,$<) $< -MF $@

%.o: %.c %.d %.h
	@$(MKDIR) $(dir $@)
	$(CC) $(CFLAGS) -o $@ -c $<

libvge.a: $(OBJECTS)
	ar rcs $@ $^
.DEFAULT_GOAL:=libvge.a

tests/tests_gen.c: tests/setup.py
	cd tests && ./setup.py

vgetests: $(TEST_OBJECTS) libvge.a tests/tests_gen.c
	$(CC) $(LDLIBS) $(TEST_OBJECTS) -L. -lvge -o $@

PROJECTSDIR=./projects
PROJECT_DIRS=$(shell find $(PROJECTSDIR) -mindepth 1 -maxdepth 1 -type d)
PROJECTS=$(notdir $(PROJECT_DIRS))

define make-project-target
$1: $(patsubst %.c,%.o,$(shell find "$(PROJECTSDIR)/$1" -type f -name "*.c")) libvge.a
	$(CC) $(LDLIBS) $(patsubst %.c,%.o,$(shell find "$(PROJECTSDIR)/$1" -type f -name "*.c")) -L. -lvge -o $1
endef

$(foreach proj, $(PROJECTS), $(eval $(call make-project-target,$(proj))))

.PHONY: clean
clean:
	echo $(PROJECTS)
	rm -f libvge.a $(OBJECTS) $(DEPFILES) $(TEST_OBJECTS) $(TEST_DEPFILES)
