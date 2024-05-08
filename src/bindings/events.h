#ifndef __LU5_EVENTS_BINDINGS__
#define __LU5_EVENTS_BINDINGS__

#include <lua.h>

/**
 * Check if a keyboard key is pressed, returns `true` if key is down and returns `false` if it's not
 * 
 * @param k The keyboard key to check
 *
 * @return boolean Whether or not the key is down
 */
int isKeyDown(lua_State *L);

/**
 * @brief mousePressed
 * 
 * Called when a mouse button is pressed.
 *
 * @param button The pressed mouse button
 *
 * <br/>
 * In the following example, the circle's size increases when the user clicks the mouse.
 *
 * @example
 * size = 0;
 *
 * function setup()
 *   createWindow(400, 400);
 * end
 *
 * function draw()
 *   background(51);
 *
 *   circle(mouseX, mouseY, size);
 * end
 *
 * -- Increase circle size when mouse pressed
 * function mousePressed()
 *   size = size + 1;
 * end
 * @example
 *
 */

/**
 * @brief mouseReleased
 * 
 * Called when a mouse button is released.
 *
 * @param button The released mouse button
 *
 * <br/>
 * In the following example, the circle's size increases when the user clicks the mouse.
 *
 * @example
 * size = 32;
 *
 * function setup()
 *   createWindow(400, 400);
 * end
 *
 * function draw()
 *   background(51);
 *
 *   circle(mouseX, mouseY, size);
 * end
 *
 * -- Set larger circle size
 * function mousePressed()
 *   size = 64;
 * end
 *
 * -- Reset size
 * function mouseReleased()
 *   size = 32;
 * end
 * @example
 */

/**
 * @brief keyPressed
 * 
 * Called whenever a key is pressed.
 *
 * @param key The pressed key
 *
 */ 

/**
 * @brief keyReleased
 * 
 * Called whenever a key is released.
 *
 * @param key The released key
 */ 

/**
 * @brief keyHeld
 * 
 * Called whenever a key is held down.
 *
 * @param key The held key
 */ 

#endif
