PLATFORM ?= gnu

APP_NAME = lu5

SRCDIR = src
BINDIR = bin

DOC_BUILD_SCRIPT = build_docs.lua

ifeq ($(PLATFORM), win)
	CC := x86_64-w64-mingw32-gcc
else
	CC := gcc
endif

ifeq ($(PLATFORM), win)
	BIN = $(BINDIR)/win64/$(APP_NAME).exe
	OBJDIR = $(BINDIR)/win64/obj
else
	BIN = $(BINDIR)/linux/$(APP_NAME)
	OBJDIR = $(BINDIR)/linux/obj
endif

ifeq ($(PLATFORM), win)
	CFLAGS = -Wall -I/usr/x86_64-w64-mingw32/include -L/usr/x86_64-w64-mingw32/lib 

	LDFLAGS := -L/usr/x86_64-w64-mingw32\
				-lglfw3\
				-lopengl32\
				-lgdi32\
				-llua\
				-lm 
else
	CFLAGS = -Wall -I/usr/include -L/usr/lib
	LDFLAGS := -L/usr/lib -lglfw -llua -lGL -lm -lrt -ldl
endif

SOURCES = $(wildcard $(SRCDIR)/*.c) $(wildcard $(SRCDIR)/bindings/*.c)
OBJECTS := $(patsubst src/%.c,$(OBJDIR)/%.o,$(SOURCES))
DEP = $(OBJECTS:.o=.d)

all: $(BIN)

test:
	echo $(OBJECTS)

-include $(DEP)

$(OBJDIR)/%.o: src/%.c 
	@mkdir -p $(dir $@)
	$(CC) -static -MMD -c $< -o $@ $(CFLAGS)

$(BIN): $(OBJECTS)
	@mkdir -p $(dir $@)
ifeq ($(PLATFORM), win)
	$(CC) -static -o $@ $^ $(LDFLAGS)
else
	$(CC) -o $@ $^ $(LDFLAGS)
endif


.PHONY: all clean install docs win

run: $(BIN)
	$(BIN)

docs: $(BIN)
	$(BIN) ./tasks/$(DOC_BUILD_SCRIPT)

install: 
	cp $(BIN) /usr/bin/$(APP_NAME)

clean: 
	rm -fr bin/*
	rm -fr docs/*.html


