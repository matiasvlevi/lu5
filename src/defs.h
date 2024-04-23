#ifndef __DEFS_H__
#define __DEFS_H__

#include <raylib.h>

#define LUA_ADD_CONST_NUMBER_GLOBAL(name)        lua_pushnumber(L, name); lua_setglobal(L, #name)
#define LUA_ADD_NUMBER_GLOBAL(name, value) lua_pushnumber(L, value); lua_setglobal(L, name)

#define LUA_ADD_FUNCTION(name) lua_pushcfunction(L, name); lua_setglobal(L, #name)

#define LUA_PCALL(name, argc, resc, s)\
    lua_getglobal(L, name); \
    if (lua_pcall(L, argc, resc, s) != LUA_OK) {\
        fprintf(stderr, "[\x1b[91mERROR\x1b[0m]: %s\n", lua_tostring(L, -1));\
        return 1;\
    }\

#define LU5_NO_WINDOW_ERROR\
    "You need to create a window with the `createWindow` function\n"

#define LU5_FILE_NOT_SPECIFIED\
    "No source path found\n"

#define LU5_FILE_NOT_EXIST(filename)\
    "'%s' is not a valid lua sketch file\n", filename

#define LU5_FILE_EXISTS_ERROR(x)\
    "It seems that %s already exists\n"\
    "We will not overwrite the file\n", x

#define LU5_RUNNING_FILE(filename)\
    "\x1b[46m\x1b[30mRunning >>> \x1b[0m \x1b[36m%s\x1b[0m\n", filename

#define LU5_LUA_ERROR(content)\
    "\n\x1b[31mERROR\x1b[0m %s\n\n", content

#define LU5_CLOSE\
    "Terminating...\n"

#define LU5_SKETCH_BOILERPLATE \
        "\n"\
        "function setup()\n"\
        "   createWindow(600, 600);\n"\
        "end\n"\
        "\n"\
        "function draw()\n"\
        "   background(51);\n"\
        "end\n"\

typedef struct {
    Color fill;
    Color stroke;
    int font_size;
} Options;

#endif
