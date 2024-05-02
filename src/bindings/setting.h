#ifndef __LU5_SETTING_BINDINGS__
#define __LU5_SETTING_BINDINGS__

#include <lua.h>

/**
 * Set the fill color for shapes
 *
 * @param r The red byte
 * @param g The green byte
 * @param b The blue byte
 * @param a The alpha byte
 *
 */ 
int fill(lua_State *L);

/**
* Set the line width
*
* @param weight The line width in pixels
*/
int strokeWeight(lua_State *L);

/**
 * Disable fill
 */
int noFill(lua_State *L);

/**
 * Set the stroke color for shapes
 *
 *
 * @param r The red byte
 * @param g The green byte
 * @param b The blue byte
 * @param a The alpha byte
 *
 */ 
int stroke(lua_State *L);

/**
 * Disable stroke
 */ 
int noStroke(lua_State *L);


#endif
