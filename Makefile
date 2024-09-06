# Build for Linux & Windows
# 
# This Makefile is intended for use on a linux system

PLATFORM ?= gnu

APP_NAME = lu5
VERSION = 0.1.7
LUA_VERSION=5.4.7

SRCDIR = src
BINDIR = bin
DOC_BUILD_SCRIPT = build_docs.lua

MACROS=-D'LU5_VERSION="$(VERSION)"'
MINGW=/usr/x86_64-w64-mingw32/
LUA_DEST=include/lua
LUA_SRC =include/lua
LUA_STATIC=$(LUA_SRC)/liblua.a

NSIS_PATH := ~/.wine/drive_c/Program\ Files\ \(x86\)/NSIS/makensis.exe

INSTALLER_NAME := lu5-x86_64-win-$(VERSION).exe
INSTALLER_SCRIPT := installer/lu5_installer.nsi
INSTALLER_EXEC := $(BINDIR)/win64/$(INSTALLER_NAME)

ifeq ($(PLATFORM), win)
	CC := x86_64-w64-mingw32-gcc
	BIN = $(BINDIR)/win64/$(APP_NAME).exe
	OBJDIR = $(BINDIR)/win64/obj
	CFLAGS = -Wall\
		-I/usr/x86_64-w64-mingw32/include\
		-I/usr/x86_64-w64-mingw32/include/freetype2

	LDFLAGS := -L/usr/x86_64-w64-mingw32/lib\
		-lfreetype\
		-lglfw3\
		-lglu32\
		-lopengl32\
		-lgdi32\
		-llua\
		-pthread\
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
		  $(wildcard $(SRCDIR)/geometry/3D/*.c)

OBJECTS := $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SOURCES))
DEP = $(OBJECTS:.o=.d)

EXAMPLES = $(wildcard examples/*.lua)
PROJECTS = $(wildcard examples/projects/**/main.lua)
TESTS = $(wildcard tests/*.lua)

ifeq ($(PLATFORM), win)
all: $(INSTALLER_EXEC)
else
all: $(BIN)
endif

-include $(DEP)


$(OBJDIR)/%.o: src/%.c $(LUA_STATIC)
	@mkdir -p $(dir $@)
	$(CC) -MMD -c $< -o $@ $(CFLAGS) $(MACROS)

$(BIN): $(OBJECTS)
	@mkdir -p $(dir $@)
ifeq ($(PLATFORM), win)
	cp /usr/x86_64-w64-mingw32/bin/zlib1.dll $(BINDIR)/win64/zlib1.dll
	cp /usr/x86_64-w64-mingw32/bin/libssp-0.dll $(BINDIR)/win64/libssp-0.dll
	cp /usr/x86_64-w64-mingw32/bin/libbrotlicommon.dll $(BINDIR)/win64/libbrotlicommon.dll
	cp /usr/x86_64-w64-mingw32/bin/libbrotlidec.dll $(BINDIR)/win64/libbrotlidec.dll
	cp /usr/x86_64-w64-mingw32/bin/libbz2-1.dll $(BINDIR)/win64/libbz2-1.dll
	cp /usr/x86_64-w64-mingw32/bin/libbrotlidec.dll $(BINDIR)/win64/libbrotlidec.dll
	cp /usr/x86_64-w64-mingw32/bin/lua54.dll $(BINDIR)/win64/lua54.dll
	cp /usr/x86_64-w64-mingw32/bin/libfreetype-6.dll $(BINDIR)/win64/libfreetype-6.dll
	cp /usr/x86_64-w64-mingw32/bin/libwinpthread-1.dll $(BINDIR)/win64/libwinpthread-1.dll

	$(CC) -o $@ $^ $(LDFLAGS)
else
	$(CC) -o $@ $^ $(LUA_STATIC) $(LDFLAGS)
endif

.PHONY: all clean install docs zip examples tests

SCRIPT ?= ./test.lua

# Build
$(LUA_STATIC): $(LUA_DEST)
	cd $(LUA_DEST) && make

# Run unit tests
tests: $(all) $(TESTS:=.run)
tests/%.lua.run: tests/%.lua 
	$(BIN) --log 2 $<
	rm -f $@

# Run a lu5 script with the latest build
run: $(BIN) $(SCRIPT)
	$(BIN) $(SCRIPT)

# Run all examples
examples: $(all) $(EXAMPLES:=.run)
examples/%.lua.run: examples/%.lua 
	$(BIN) --log 5 $<
	rm -f $@

# Run all example projects
projects: $(all) $(PROJECTS:=.run)
projects/%.lua.run: examples/projects/%/main.lua 
	$(BIN) $<
	rm -f $@

# Build the documentation using lu5 and task scripts
docs: $(BIN)
	$(BIN) ./tasks/$(DOC_BUILD_SCRIPT)

# Install
ifeq ($(PLATFORM), win)

$(INSTALLER_EXEC): $(INSTALLER_SCRIPT) $(BIN)
	@echo "Compiling NSIS script..."
	wine $(NSIS_PATH) $(INSTALLER_SCRIPT)

zip: $(INSTALLER_EXEC)
	zip $(BINDIR)/win64/lu5-x86_64-win-$(VERSION).zip $(INSTALLER_EXEC)

else

zip: $(BIN)
	zip $(BINDIR)/linux/lu5-x86_64-linux-$(VERSION).zip $(BIN)

install: 
	cp $(BIN) /usr/bin/$(APP_NAME)

endif

clean:
	rm -fr bin/linux
	rm -fr bin/win64
	rm -fr $(INSTALLER_EXEC)
	rm -fr include/lua/liblua.a
	rm -fr docs/assets/*.svg
	rm -fr docs/assets/*.css
	rm -fr docs/assets/*.js
	rm -fr examples/*.lua.run


