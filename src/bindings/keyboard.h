#ifndef _LU5_KEYBOARD_
#define _LU5_KEYBOARD_

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
