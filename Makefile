# Build for Linux, Windows & WASM
# 
# This Makefile is intended for use on a linux system

# linux, wasm, win
PLATFORM ?= linux

APP_NAME = lu5
VERSION = 0.1.7
LUA_VERSION=5.4.7

SRCDIR = src
BINDIR = bin

MACROS=-D'LU5_VERSION="$(VERSION)"'
LUA_SRC=include/lua

LUA_A = $(LUA_SRC)/liblua.a

AGNOSTIC_SRC =\
		  $(wildcard $(SRCDIR)/*.c)\
		  $(wildcard $(SRCDIR)/bindings/*.c)
ALL_SRC = $(AGNOSTIC_SRC)\
		  $(wildcard $(SRCDIR)/platform/*.c)\
		  $(wildcard $(SRCDIR)/platform/geometry/2D/*.c)\
		  $(wildcard $(SRCDIR)/platform/geometry/3D/*.c)
HEADERS = $(wildcard $(SRCDIR)/*.h)

ifeq ($(PLATFORM), linux)
	OBJ_EXT = .o
	LIB_EXT = .a
	BIN_EXT =

	CC := gcc
	BIN = $(BINDIR)/$(PLATFORM)/$(APP_NAME)
	OBJDIR = $(BINDIR)/$(PLATFORM)/obj
	CFLAGS = -Wall\
		-I$(LUA_SRC)\
		$(shell pkg-config --cflags glfw3)\
		$(shell pkg-config --cflags glew)\
		$(shell pkg-config --cflags gl)\
		$(shell pkg-config --cflags freetype2)
	LDFLAGS :=\
		-L$(LUA_SRC)\
		$(shell pkg-config --static --libs glfw3)\
		$(shell pkg-config --static --libs glew)\
		$(shell pkg-config --static --libs gl)\
		$(shell pkg-config --libs freetype2)\
		-lm

	SOURCES=$(ALL_SRC)
else ifeq ($(PLATFORM), wasm)

	OBJ_EXT = .o.wasm
	LIB_EXT = .a.wasm
	BIN_EXT = .wasm

	# WASM setup
	WASI_SDK_PATH ?= /opt/wasi-sdk-24
	CC := $(WASI_SDK_PATH)/bin/clang
	AR := $(WASI_SDK_PATH)/bin/llvm-ar
	RANLIB := $(WASI_SDK_PATH)/bin/llvm-ranlib

	BIN = $(BINDIR)/$(PLATFORM)/$(APP_NAME)$(BIN_EXT)
	OBJDIR = $(BINDIR)/$(PLATFORM)/obj
	CFLAGS = \
		-mllvm -wasm-enable-sjlj\
		--target=wasm32-wasi\
		--sysroot=$(WASI_SDK_PATH)/share/wasi-sysroot\
		-I$(WASI_SDK_PATH)/share/wasi-sysroot/include\
		-I$(LUA_SRC)\
		-DLU5_WASM\
		-D_WASI_EMULATED_SIGNAL\
		-D_WASI_EMULATED_PROCESS_CLOCKS\
		-DLUA_USE_C89

	LDFLAGS = \
		--sysroot=$(WASI_SDK_PATH)/share/wasi-sysroot\
		--target=wasm32-wasi\
		-Wl,-u__wasm_longjmp\
		-lsetjmp\
		-lwasi-emulated-process-clocks\
		-Wl,-mllvm,-wasm-enable-sjlj\
		-Wl,--export=malloc,\
		-Wl,--export=free,\
		-Wl,--no-entry,

	SOURCES=$(AGNOSTIC_SRC)

	LUA_A := $(LUA_A:.a=$(LIB_EXT))

else ifeq ($(PLATFORM), win)
	OBJ_EXT = .o
	LIB_EXT = .a
	BIN_EXT = .exe

	ARCH=x86_64-w64-mingw32
	CC := $(ARCH)-gcc
	MINGW = /usr/x86_64-w64-mingw32/
	NSIS_PATH := ~/.wine/drive_c/Program\ Files\ \(x86\)/NSIS/makensis.exe
	INSTALLER_NAME := lu5_installer-$(VERSION).exe
	INSTALLER_SCRIPT := installer/lu5_installer.nsi
	INSTALLER_EXEC := $(BINDIR)/$(PLATFORM)/$(INSTALLER_NAME)

	BIN = $(BINDIR)/$(PLATFORM)/$(APP_NAME)$(BIN_EXT)
	OBJDIR = $(BINDIR)/$(PLATFORM)/obj
	CFLAGS = -Wall\
		-I/usr/$(ARCH)/include\
		-I/usr/$(ARCH)/include/freetype2\
		-L/usr/$(ARCH)/lib
		
	LDFLAGS :=\
		-lfreetype\
		-lglfw3\
		-lglu32\
		-lgdi32\
		-lopengl32\
		-llua

	DLL_FILES = \
		zlib1.dll \
		libssp-0.dll \
		libbrotlicommon.dll \
		libbrotlidec.dll \
		libbz2-1.dll \
		lua54.dll \
		libfreetype-6.dll \
		libwinpthread-1.dll

	SOURCES=$(ALL_SRC)
endif

OBJECTS := $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%$(OBJ_EXT),$(SOURCES))

all: $(BIN)

# Build lua static library
$(LUA_A):
	cd $(LUA_SRC) && make PLATFORM=$(PLATFORM)

# Build object files
$(OBJDIR)/%$(OBJ_EXT): src/%.c $(LUA_A) $(HEADERS)
	@mkdir -p $(dir $@)
	$(CC) -MMD -c $< -o $@ $(CFLAGS) $(MACROS)

# Rule to build .wat files from .wasm files
$(OBJDIR)/%.wat: $(OBJDIR)/%$(OBJ_EXT)
	wasm2wat $< -o $@ --enable-all

debug: $(OBJECTS:$(OBJ_EXT)=.wat)

# Link all togheter
$(BIN): $(OBJECTS) $(LUA_A)
	@mkdir -p $(dir $@)
	$(CC) -o $@ $^  $(CFLAGS) $(LDFLAGS)

# ---
# Build the documentation using lu5 and lua scripts
#
# `make docs`
#
# See `site/config.lua`
# ---
DOC_BUILD_TASK = site/tasks/build_docs.lua
docs: $(BIN) $(SOURCES)
	$(BIN) $(DOC_BUILD_TASK)

# ---
# Run a lu5 script with the latest build
#
# `make run` will run `./test.lua`
# `make run SCRIPT=foo.lua` will run `foo.lua`
#
# ---
SCRIPT ?= ./test.lua
run: $(BIN) $(SCRIPT)
	$(BIN) $(SCRIPT)

examples:
	cd examples && make

# ---
# Run non-graphical unit tests
#
# `make tests`
# ---
TESTS = $(wildcard tests/*.lua)
tests: $(all) $(TESTS:=.run)
tests/%.lua.run: tests/%.lua 
	$(BIN) --log 2 $<
	rm -f $@

ifeq ($(PLATFORM), win)

# Copy all DLLs from mingw to build destination
$(BINDIR)/$(PLATFORM)/%.dll: /usr/x86_64-w64-mingw32/bin/%.dll
	cp $< $@

# Build windows installer
$(INSTALLER_EXEC): $(INSTALLER_SCRIPT) $(BIN) $(DLL_FILES:%=$(BINDIR)/$(PLATFORM)/%)
	wine $(NSIS_PATH) $<

# Command to build the installer
installer: $(INSTALLER_EXEC)

else 
# Zip binary
zip: $(BIN)
	zip $(BINDIR)/$(PLATFORM)/lu5-x86_64-$(PLATFORM)-$(VERSION).zip $(BIN)

endif

clean:
	cd include/lua && make clean
	rm -fr $(BINDIR)/wasm
	rm -fr $(BINDIR)/win
	rm -fr $(BINDIR)/linux
	rm -fr $(INSTALLER_EXEC)
	rm -fr docs/assets/*.svg
	rm -fr docs/assets/*.css
	rm -fr docs/assets/*.js
	rm -fr examples/*.lua.run

.PHONY: all clean docs zip examples tests installer