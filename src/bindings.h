#ifndef __LU5_BINDINGS__
#define __LU5_BINDINGS__

#include <lua.h>
#include <GLFW/glfw3.h>

#include <stdbool.h>

int createWindow(lua_State *L);

int background(lua_State *L);

#define LU5_CIRCLE_SEGMENTS 36
int circle(lua_State *L);

int rect(lua_State *L);

int line(lua_State *L);

int text(lua_State *L);

int fill(lua_State *L);

int strokeWeight(lua_State *L);

int isKeyDown(lua_State *L);

int isMouseDown(lua_State *L);

int print(lua_State *L);

//

void lu5_update_dynamic_variables(lua_State *L, GLFWwindow *window);
   
void lu5_register_symbols(lua_State *L);

#endif
