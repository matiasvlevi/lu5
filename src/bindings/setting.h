#ifndef __LU5_SETTING_BINDINGS__
#define __LU5_SETTING_BINDINGS__

#include <lua.h>

/**
 * Set the fill color for shapes
 *
 * @param r The red byte
 * @param g The green byte
 * @param b The blue byte
 * @param [a] The alpha byte
 *
 * Can also accept a hexadecimal or color name as string
 *
 * @example
 * fill(255, 150, 40);
 * square(200, 200, 64);
 * @example
 * 
 */ 
int fill(lua_State *L);

/**
* Set the line width
*
* @param weight The line width in pixels
*
* @example
* strokeWeight(8);
* line(200, 200, mouseX, mouseY);
* @example
*/
int strokeWeight(lua_State *L);

/**
 * Disable fill
 *
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

/**
 * Set the font size
 *
 * @param size The size of the font in pixels
 */
int textSize(lua_State *L);

#endif
