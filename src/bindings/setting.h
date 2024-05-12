#ifndef __LU5_SETTING_BINDINGS__
#define __LU5_SETTING_BINDINGS__

#include <lua.h>

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
* Currently is only implemented for `line` and partially implemented for `circle`
*
* @example
* strokeWeight(8);
* line(200, 200, mouseX, mouseY);
* @example
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
 * Only implemented for `line` and `circle`
 *
 */ 
int stroke(lua_State *L);

/**
 * Disable stroke
 *
 * Only implemented for `line` and `circle`
 */ 
int noStroke(lua_State *L);

/**
 * Save the style settings
 */
int push(lua_State *L);

/**
 * Restore the style settings 
 */
int pop(lua_State *L);

#endif
