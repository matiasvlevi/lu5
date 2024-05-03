#ifndef _LU5_LOADERS_H_
#define _LU5_LOADERS_H_

#include <lua.h>

/**
 * Load a font face
 * 
 * @param path The font path on the local system
 * 
 * @example
 * function setup()
 *   createWindow(600, 600);
 *   loadFont('/path/to/your/font.ttf');
 * end
 *
 * function draw()
 *   background(51);
 *
 *   text('Hello from lu5!', 30, 50);
 * end   
 * @example
 */
int loadFont(lua_State *L);

int loadImage(lua_State *L);

int loadJSON(lua_State *L);

int loadCSV(lua_State *L);

int loadText(lua_State *L);

#endif