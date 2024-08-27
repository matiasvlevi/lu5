PLATFORM ?= gnu

APP_NAME = lu5
VERSION = 0.1.6
LUA_VERSION=5.4.7

SRCDIR = src
BINDIR = bin
DOC_BUILD_SCRIPT = build_docs.lua

MACROS=-D'LU5_VERSION="$(VERSION)"'

LUA_DEST=lua
LUA_SRC =$(LUA_DEST)
LUA_STATIC=$(LUA_SRC)/liblua.a

ifeq ($(PLATFORM), win)
	CC := x86_64-w64-mingw32-gcc
	BIN = $(BINDIR)/win64/$(APP_NAME).exe
	OBJDIR = $(BINDIR)/win64/obj
	CFLAGS = -Wall\
	-I/usr/x86_64-w64-mingw32/include\
	-L/usr/x86_64-w64-mingw32/lib\
	-I/usr/x86_64-w64-mingw32/include/freetype2\
	-I/usr/x86_64-w64-mingw32/include/libpng16\
	-I/usr/x86_64-w64-mingw32/include/harfbuzz\
	-I/usr/x86_64-w64-mingw32/include/glib-2.0\
	-I/usr/x86_64-w64-mingw32/lib/glib-2.0/include\
	-I/usr/x86_64-w64-mingw32/include/sysprof-6\
	-pthread\

	LDFLAGS := -L/usr/x86_64-w64-mingw32\
				-static \
				$(shell pkg-config --static --libs freetype2)\
			   	-static-libgcc \
			   	-static-libstdc++ \
				-lglfw3\
				-lopengl32\
				-lgdi32\
				-llua\
				-lm
else
	CC := gcc
	BIN = $(BINDIR)/linux/$(APP_NAME)
	OBJDIR = $(BINDIR)/linux/obj
	CFLAGS = -Wall\
		-I$(LUA_SRC)\
		$(shell pkg-config --cflags glfw3)\
		$(shell pkg-config --cflags glew)\
		$(shell pkg-config --cflags glu)\
		$(shell pkg-config --cflags gl)\
		$(shell pkg-config --cflags freetype2)
	LDFLAGS :=\
		-L$(LUA_SRC)\
		$(shell pkg-config --static --libs glfw3)\
		$(shell pkg-config --static --libs glew)\
		$(shell pkg-config --static --libs gl)\
		$(shell pkg-config --libs freetype2)\
		-lm
endif

SOURCES = $(wildcard $(SRCDIR)/*.c)\
		  $(wildcard $(SRCDIR)/bindings/*.c)\
		  $(wildcard $(SRCDIR)/geometry/2D/*.c)\
		  $(wildcard $(SRCDIR)/geometry/3D/*.c)\
		  $(wildcard $(SRCDIR)/shaders/*.c)

OBJECTS := $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SOURCES))
DEP = $(OBJECTS:.o=.d)

EXAMPLES = $(wildcard examples/*.lua)
PROJECTS = $(wildcard examples/projects/**/main.lua)
TESTS = $(wildcard tests/*.lua)

all: $(BIN)

-include $(DEP)

$(OBJDIR)/%.o: src/%.c $(LUA_STATIC)
	@mkdir -p $(dir $@)
	$(CC) -static -MMD  $(MACROS) -c $< -o $@ $(CFLAGS)

$(BIN): $(OBJECTS)
	@mkdir -p $(dir $@)
ifeq ($(PLATFORM), win)
	$(CC) -static -o $@ $^ $(LDFLAGS) 
else
	$(CC) -o $@ $^ $(LUA_STATIC) $(LDFLAGS)
endif

.PHONY: all clean install docs zip examples tests

SCRIPT ?= ./test.lua

$(LUA_STATIC): $(LUA_DEST)
	cd $(LUA_DEST) && make

run: $(BIN) $(SCRIPT)
	$(BIN) $(SCRIPT)

examples: $(all) $(EXAMPLES:=.run)

examples/%.lua.run: examples/%.lua 
	$(BIN) $<
	rm -f $@

tests: $(all) $(TESTS:=.run)

tests/%.lua.run: tests/%.lua 
	$(BIN) --log 2 $<
	rm -f $@

projects: $(all) $(PROJECTS:=.run)

projects/%.lua.run: examples/projects/%/main.lua 
	$(BIN) $<
	rm -f $@

docs: $(BIN)
	$(BIN) ./tasks/$(DOC_BUILD_SCRIPT)

zip:
	zip $(BINDIR)/linux/lu5-x86_64-linux-$(VERSION).zip $(BIN)

install: 
	cp $(BIN) /usr/bin/$(APP_NAME)

clean:
	rm -fr bin/*
	rm -fr docs/latest/*
	rm -fr docs/assets/*.svg
	rm -fr docs/assets/*.css
	rm -fr docs/assets/*.js
	rm -fr examples/*.lua.run


