#ifndef __DEFS_H__
#define __DEFS_H__

#include <raylib.h>

#define LUA_ADD_CONST_NUMBER_GLOBAL(name)        lua_pushnumber(L, name); lua_setglobal(L, #name)
#define LUA_ADD_NUMBER_GLOBAL(name, value) lua_pushnumber(L, value); lua_setglobal(L, name)

#define LUA_ADD_FUNCTION(name) lua_pushcfunction(L, name); lua_setglobal(L, #name)

#define LUA_PCALL(name, argc, resc, s)\
    lua_getglobal(L, name); \
    if (lua_pcall(L, argc, resc, s) != LUA_OK) {\
        fprintf(stderr, "Lua error: %s\n", lua_tostring(L, -1));\
        return 1;\
    }\

typedef struct {
    Color fill;
    Color stroke;
    int font_size;
} Options;

#endif
