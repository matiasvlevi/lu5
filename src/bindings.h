#ifndef __LU5_BINDINGS__
#define __LU5_BINDINGS__

#include <lua.h>
#include <GLFW/glfw3.h>

#include <stdbool.h>

extern bool windowExists;

int createWindow(lua_State *L);

int background(lua_State *L);

int circle(lua_State *L);

int rect(lua_State *L);

int text(lua_State *L);

int fill(lua_State *L);

int isKeyDown(lua_State *L);

int isKeyPressed(lua_State *L);

int print(lua_State *L);

void update_dynamic_variables(lua_State *L, GLFWwindow *window);
   
void registerSymbols(lua_State *L);

#endif
