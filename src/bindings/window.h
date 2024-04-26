#ifndef __LU5_WINDOW_BINDINGS__
#define __LU5_WINDOW_BINDINGS__

#include <lua.h>

/**
 * Create an opengl context and a GLFW window
 *
 * @param w Window width
 * @param h Window height
 */ 
int createWindow(lua_State *L);

/**
 * Set a background on the screen
 *
 * @param r The red byte
 * @param g The green byte
 * @param b The blue byte
 * @param a The alpha byte
 *
 */ 
int background(lua_State *L);

#endif
