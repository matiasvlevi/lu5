# Define required macros here
SHELL = /bin/sh

SFML_PATH = /usr/local
CC = gcc

OBJ = $(patsubst src/%.c,bin/%.o,$(wildcard $(shell find src -type f -name '*.c')))
DEP = $(OBJ:.o=.d)

BIN = ./bin/lu5
LFLAGS = -lm -llua -lglfw -lGLEW -lGL

all: $(BIN)

-include $(DEP)

bin/%.o: src/%.c 
	@mkdir -p $(dir $@)
	$(CC) -MMD -c $< -o $@

$(BIN): $(OBJ)
	$(CC) -o $@ $^ $(LFLAGS)

install: 
	cp ./bin/lu5 /usr/bin/lu5

clean: 
	rm -fr bin/*

.PHONY: all run clean
