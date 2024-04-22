#include <stdio.h>
#include <stdlib.h>

#include "readFile.h"
#include "colorArgs.h"

#include <math.h>

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

#include <raylib.h>

#define LUA_NUMBER_CONSTANT(name)   lua_pushnumber(L, name); lua_setglobal(L, #name);
#define LUA_REGISTER_FUNCTION(name) lua_pushcfunction(L, name); lua_setglobal(L, #name);

#define LUA_PCALL(name, argc, resc, s) \
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

static Options options = {
    .fill   = (Color){0xff,0xff,0xff,0xff},
    .stroke = (Color){0x00,0x00,0x00,0x00},
    .font_size = 24
}; 

void lu5_string_from_arg(lua_State *L, char *str, int argc) {
    str = (char*)luaL_checkstring(L, argc);
    if (!str) {
        luaL_error(L, "Expected a string argument");
        return;
    }
}

static bool windowExists = false;

/* C function to be called from Lua */
static int createWindow(lua_State *L) {
    
    int screenWidth = lua_tonumber(L, 1);
    int screenHeight = lua_tonumber(L, 2);
    
    InitWindow(screenWidth, screenHeight, "luaP5");
    SetTargetFPS(60);

    lua_pushnumber(L, screenWidth);
    lua_setglobal(L, "width");

    lua_pushnumber(L, screenHeight);
    lua_setglobal(L, "height");

    windowExists = true;

    return 0;
}

static int background(lua_State *L) {
    Color color = rgbColorFromLuaArguments(L);

    ClearBackground(color);

    return 0;
}

static int circle(lua_State *L) {
    int x = lua_tonumber(L, 1);  
    int y = lua_tonumber(L, 2);  
    double r = lua_tonumber(L, 3);  

    DrawCircle(x, y, r, options.fill);

    return 0;
}

static int rect(lua_State *L) {
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

static int text(lua_State *L)
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

static int fill(lua_State *L) 
{
    options.fill = rgbColorFromLuaArguments(L); 

    return 0;
}

static int isKeyDown(lua_State *L) 
{
    unsigned int key = lua_tonumber(L, 1);
    
    bool ret = IsKeyDown(key);
    lua_pushboolean(L, ret);
    return 1;
}

static int isKeyPressed(lua_State *L) 
{
    unsigned int key = lua_tonumber(L, 1);
    
    bool ret = IsKeyPressed(key);
    lua_pushboolean(L, ret);
    return 1;
}

static int print(lua_State *L)
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

void registerFunctions(lua_State *L) 
{
    LUA_REGISTER_FUNCTION(print);
    
    LUA_REGISTER_FUNCTION(createWindow);
    
    LUA_REGISTER_FUNCTION(background);
    LUA_REGISTER_FUNCTION(fill);


    LUA_REGISTER_FUNCTION(text);
    LUA_REGISTER_FUNCTION(circle);
    LUA_REGISTER_FUNCTION(rect); 

    LUA_REGISTER_FUNCTION(isKeyPressed);
    LUA_REGISTER_FUNCTION(isKeyDown);

    LUA_NUMBER_CONSTANT(KEY_RIGHT);
    LUA_NUMBER_CONSTANT(KEY_LEFT);
    LUA_NUMBER_CONSTANT(KEY_UP);
    LUA_NUMBER_CONSTANT(KEY_DOWN);
    LUA_NUMBER_CONSTANT(KEY_ENTER);
    LUA_NUMBER_CONSTANT(KEY_BACKSPACE);
}

int main(int argc, char **argv) {

    if (argc < 2) {
        puts("File name required as first argument.");
        return 1;
    };

    FILE *lua_file = fopen(argv[1], "r");
    if (!lua_file) {
        fprintf(stderr, "Could not find lua source file\n");
        return 1;
    }

    char *lua_source = readFile(lua_file);

    lua_State *L = luaL_newstate();
    luaL_openlibs(L);

    registerFunctions(L);

    if (luaL_dostring(L, lua_source) != LUA_OK) {
        fprintf(stderr, "Lua error: %s", lua_tostring(L, -1));
    }

    LUA_PCALL("setup", 0, 0, 0)
 
    if (windowExists) {
        while (!WindowShouldClose()) {
            BeginDrawing();
             
            LUA_PCALL("draw", 0, 0, 0)
            
            EndDrawing();
        }
        
        CloseWindow();
    } else {
        fprintf(stderr, "You need to create a window with the `createWindow` function\n");
        return 1;
    }

    lua_close(L);
    free(lua_source);

    return 0;
}
