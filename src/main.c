#include <stdio.h>
#include <stdlib.h>

#include "readFile.h"
#include "colorArgs.h"

#include <math.h>

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

#include <raylib.h>



#define LUA_ADD_CONST_NUMBER_GLOBAL(name)        lua_pushnumber(L, name); lua_setglobal(L, #name);
#define LUA_ADD_NUMBER_GLOBAL(name, value) lua_pushnumber(L, value); lua_setglobal(L, name);

#define LUA_ADD_FUNCTION(name) lua_pushcfunction(L, name); lua_setglobal(L, #name);

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

static void update_dynamic_variables(lua_State *L) {
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


void handle_args(char** argv) 
{
    
}

int main(int argc, char **argv) {

    for (int i = 0; i < argc; i++) {
        printf("Arg %i: %s\n", i, argv[i]);
    }

    if (argc < 2) {
        puts("File name required as first argument.");
        return 1;
    };

    // Read the specified file
    FILE *lua_file = fopen(argv[1], "r");
    if (!lua_file) {
        fprintf(stderr, "Could not find lua source file\n");
        return 1;
    }
    char *lua_source = readFile(lua_file);

    // Start lua
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);

    // Register functions & constants
    registerSymbols(L);
 
    // Run the file
    if (luaL_dostring(L, lua_source) != LUA_OK) {
        fprintf(stderr, "Lua error: %s", lua_tostring(L, -1));
    }

    // Call the setup function
    LUA_PCALL("setup", 0, 0, 0)
 
    // If window was created in the setup, run main loop
    if (windowExists) {
        update_dynamic_variables(L);
        
        while (!WindowShouldClose()) {
            update_dynamic_variables(L);

            BeginDrawing();
             
            // Call draw
            LUA_PCALL("draw", 0, 0, 0)
            
            EndDrawing();
        }
        
        CloseWindow();
    } else {
        fprintf(stderr, "You need to create a window with the `createWindow` function\n");
        return 1;
    }

    // Close lua
    lua_close(L);

    // Free the lua file
    free(lua_source);

    return 0;
}
