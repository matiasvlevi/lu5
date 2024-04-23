#ifndef __LU5_BINDINGS__
#define __LU5_BINDINGS__

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

#include <raylib.h>

#include "readFile.h"
#include "colorArgs.h"
#include "defs.h"

static Options options = {
    .fill   = (Color){ 0xff, 0xff, 0xff, 0xff },
    .stroke = (Color){ 0x00, 0x00, 0x00, 0x00 },
    .font_size = 24
}; 

static bool windowExists = false;

/* C function to be called from Lua */
int createWindow(lua_State *L) {
    
    int screenWidth = lua_tonumber(L, 1);
    int screenHeight = lua_tonumber(L, 2);
    
    InitWindow(screenWidth, screenHeight, "luaP5");
    SetTargetFPS(60);

    LUA_ADD_NUMBER_GLOBAL("width", screenWidth);
    LUA_ADD_NUMBER_GLOBAL("height", screenHeight);

    windowExists = true;

    return 0;
}

int background(lua_State *L) {
    Color color = rgbColorFromLuaArguments(L);

    ClearBackground(color);

    return 0;
}

int circle(lua_State *L) {
    int x = lua_tonumber(L, 1);  
    int y = lua_tonumber(L, 2);  
    double r = lua_tonumber(L, 3);  

    DrawCircle(x, y, r, options.fill);

    return 0;
}

int rect(lua_State *L) {
    int x = lua_tonumber(L, 1);  
    int y = lua_tonumber(L, 2);  
    int w = lua_tonumber(L, 3);  

    int h = w;
    if (lua_gettop(L) > 3) {
        h = lua_tonumber(L, 4);
    }  

    DrawRectangle(x, y, w, h, options.fill);

    return 0;
}

int text(lua_State *L)
{
    const char *str = luaL_checkstring(L, 1);
    if (!str) {
        luaL_error(L, "Expected a string argument");
        return 0;
    }

    int x = lua_tonumber(L, 2);
    int y = lua_tonumber(L, 3);

    DrawText(str, x, y, options.font_size, options.fill);

    return 0;
}

int fill(lua_State *L) 
{
    options.fill = rgbColorFromLuaArguments(L); 

    return 0;
}

int isKeyDown(lua_State *L) 
{
    unsigned int key = lua_tonumber(L, 1);
    
    bool ret = IsKeyDown(key);
    lua_pushboolean(L, ret);
    return 1;
}

int isKeyPressed(lua_State *L) 
{
    unsigned int key = lua_tonumber(L, 1);
    
    bool ret = IsKeyPressed(key);
    lua_pushboolean(L, ret);
    return 1;
}

int print(lua_State *L)
{
    if (lua_gettop(L) != 1) {
        luaL_error(L, "Expected a string argument");
        return 0;
    }
    const char *str = luaL_checkstring(L, 1);
    if (!str) {
        luaL_error(L, "Expected a string argument");
        return 0;
    }

    puts(str);

    return 0;
}

void update_dynamic_variables(lua_State *L) {
    LUA_ADD_NUMBER_GLOBAL("mouseX", GetMouseX());
    LUA_ADD_NUMBER_GLOBAL("mouseY", GetMouseY());
}

void registerSymbols(lua_State *L) 
{
    LUA_ADD_FUNCTION(print);
    
    LUA_ADD_FUNCTION(createWindow);
    
    LUA_ADD_FUNCTION(background);
    LUA_ADD_FUNCTION(fill);


    LUA_ADD_FUNCTION(text);
    LUA_ADD_FUNCTION(circle);
    LUA_ADD_FUNCTION(rect); 

    LUA_ADD_FUNCTION(isKeyPressed);
    LUA_ADD_FUNCTION(isKeyDown);

    LUA_ADD_CONST_NUMBER_GLOBAL(KEY_RIGHT);
    LUA_ADD_CONST_NUMBER_GLOBAL(KEY_LEFT);
    LUA_ADD_CONST_NUMBER_GLOBAL(KEY_UP);
    LUA_ADD_CONST_NUMBER_GLOBAL(KEY_DOWN);
    LUA_ADD_CONST_NUMBER_GLOBAL(KEY_ENTER);
    LUA_ADD_CONST_NUMBER_GLOBAL(KEY_BACKSPACE);
}




#endif
