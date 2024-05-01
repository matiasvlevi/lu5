#ifndef __LU5_WINDOW_BINDINGS__
#define __LU5_WINDOW_BINDINGS__

#include <lua.h>

/**
 * Create a GLFW window, if no window was created and a setup function was defined, a warning is thrown
 *
 * @param w Window width
 * @param h Window height
 */ 
int createWindow(lua_State *L);

/**
 * Clear a background with a color
 *
 * @param r The red byte
 * @param g The green byte
 * @param b The blue byte
 * @param a The alpha byte
 *
 */ 
int background(lua_State *L);

#endif
