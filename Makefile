PLATFORM ?= gnu

APP_NAME = lu5
VERSION = 0.0.4

SRCDIR = src
BINDIR = bin

DOC_BUILD_SCRIPT = build_docs.lua

MACROS=-D'LU5_VERSION="$(VERSION)"'

ifeq ($(PLATFORM), win)
	CC := x86_64-w64-mingw32-gcc
	BIN = $(BINDIR)/win64/$(APP_NAME).exe
	OBJDIR = $(BINDIR)/win64/obj
	CFLAGS = -Wall -I/usr/x86_64-w64-mingw32/include -L/usr/x86_64-w64-mingw32/lib $(shell pkg-config --cflags freetype2)
	LDFLAGS := -L/usr/x86_64-w64-mingw32\
				$(shell pkg-config --static --libs freetype2)\
				-lglfw3\
				-lopengl32\
				-lgdi32\
				-llua\
				-lm\
				-lstdc++ 
else
	CC := gcc
	BIN = $(BINDIR)/linux/$(APP_NAME)
	OBJDIR = $(BINDIR)/linux/obj
	CFLAGS = -Wall\
		$(shell pkg-config --cflags lua5.4)\
		$(shell pkg-config --cflags glfw3)\
		$(shell pkg-config --cflags glew)\
		$(shell pkg-config --cflags gl)\
		$(shell pkg-config --cflags freetype2)
	LDFLAGS :=\
		$(shell pkg-config --static --libs lua5.4)\
		$(shell pkg-config --static --libs glfw3)\
		$(shell pkg-config --static --libs glew)\
		$(shell pkg-config --static --libs gl)\
		$(shell pkg-config --libs freetype2)\
		-lm
endif

SOURCES = $(wildcard $(SRCDIR)/*.c) $(wildcard $(SRCDIR)/bindings/*.c) $(wildcard $(SRCDIR)/shaders/*.c)
OBJECTS := $(patsubst src/%.c,$(OBJDIR)/%.o,$(SOURCES))
DEP = $(OBJECTS:.o=.d)

all: $(BIN)

-include $(DEP)

$(OBJDIR)/%.o: src/%.c 
	@mkdir -p $(dir $@)
	$(CC) -static -MMD  $(MACROS) -c $< -o $@ $(CFLAGS)

$(BIN): $(OBJECTS)
	@mkdir -p $(dir $@)
ifeq ($(PLATFORM), win)
	$(CC) -static -o $@ $^ $(LDFLAGS) 
else
	$(CC) -o $@ $^ $(LDFLAGS) 
endif


.PHONY: all clean install docs zip

run: $(BIN)
	$(BIN) ./test.lua

docs: $(BIN)
	$(BIN) ./tasks/$(DOC_BUILD_SCRIPT)

zip:
	zip $(BINDIR)/linux/lu5-x86_64-linux-$(VERSION).zip $(BIN)

install: 
	cp $(BIN) /usr/bin/$(APP_NAME)

clean: 
	rm -fr bin/*
	rm -fr docs/*.html
	rm -fr docs/assets/*.svg
	rm -fr docs/assets/*.css
	rm -fr docs/assets/*.js


