# Define required macros here
SHELL = /bin/sh

SFML_PATH = /usr/local
CC = gcc

PATH_LUA=./lua/src
LUA= \
	$(PATH_LUA)/lapi.c \
	$(PATH_LUA)/lauxlib.c \
	$(PATH_LUA)/lbaselib.c \
	$(PATH_LUA)/lcode.c \
	$(PATH_LUA)/lcorolib.c \
	$(PATH_LUA)/lctype.c \
	$(PATH_LUA)/ldblib.c \
	$(PATH_LUA)/ldebug.c \
	$(PATH_LUA)/ldo.c \
	$(PATH_LUA)/ldump.c \
	$(PATH_LUA)/lfunc.c \
	$(PATH_LUA)/lgc.c \
	$(PATH_LUA)/linit.c \
	$(PATH_LUA)/liolib.c \
	$(PATH_LUA)/llex.c \
	$(PATH_LUA)/lmathlib.c \
	$(PATH_LUA)/lmem.c \
	$(PATH_LUA)/loadlib.c \
	$(PATH_LUA)/lobject.c \
	$(PATH_LUA)/lopcodes.c \
	$(PATH_LUA)/loslib.c \
	$(PATH_LUA)/lparser.c \
	$(PATH_LUA)/lstate.c \
	$(PATH_LUA)/lstring.c \
	$(PATH_LUA)/lstrlib.c \
	$(PATH_LUA)/ltable.c \
	$(PATH_LUA)/ltablib.c \
	$(PATH_LUA)/ltm.c \
	$(PATH_LUA)/lundump.c \
	$(PATH_LUA)/lutf8lib.c \
	$(PATH_LUA)/lvm.c \
	$(PATH_LUA)/lzio.c

OBJ = $(patsubst src/%.c,bin/%.o,$(wildcard $(shell find src -type f -name '*.c')))
DEP = $(OBJ:.o=.d)

BIN = ./bin/lu5
INC = -I $(SFML_PATH)/include 
LIB = -L $(SFML_PATH)/lib

LFLAGS = -llua -lm -lraylib


all: $(BIN)

-include $(DEP)

bin/%.o: src/%.c 
	@mkdir -p $(dir $@)
	$(CC) $(INC) -MMD -c $< -o $@

$(BIN): $(OBJ)
	$(CC) -o $@ $^ $(LIB) $(LFLAGS)

install: 
	mv ./bin/lu5 /usr/bin/lu5

clean: 
	rm -fr bin/*

.PHONY: all run clean
