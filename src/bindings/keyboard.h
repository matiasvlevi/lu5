#ifndef _LU5_KEYBOARD_
#define _LU5_KEYBOARD_

#include <lua.h>

/**
 * Check if a keyboard key is pressed, returns `true` if key is down and returns `false` if it's not
 * 
 * @param k The keyboard key to check as a key global, or a string
 *
 * @example
 * -- Use a string 
 * if (isKeyDown('a')) then
 *   -- key 'a' is down
 * end
 *
 * -- use a global
 * if (isKeyDown(LEFT_ARROW)) then
 *   -- left arrow is down
 * end
 * @example
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
#define LU5_KEY_PRESSED "keyPressed"

/**
 * @brief keyReleased
 * 
 * Called whenever a key is released.
 *
 * @param key The released key
 */ 
#define LU5_KEY_RELEASED "keyReleased"

/**
 * @brief keyHeld
 * 
 * Called whenever a key is held down.
 *
 * @param key The held key
 */ 
#define LU5_KEY_HELD "keyHeld"

/**
 * @brief UP_ARROW
 * @global
 * 
 */
#define LU5_KEY_UP_ARROW 265

/**
 * @brief DOWN_ARROW
 * @global
 * 
 */
#define LU5_KEY_DOWN_ARROW 264

/**
 * @brief LEFT_ARROW
 * @global
 * 
 */
#define LU5_KEY_LEFT_ARROW 263

/**
 * @brief RIGHT_ARROW
 * @global
 * 
 */
#define LU5_KEY_RIGHT_ARROW 262

/**
 * @brief ENTER
 * @global
 * 
 */
#define LU5_KEY_ENTER 257

/**
 * @brief BACKSPACE
 * @global
 * 
 */
#define LU5_KEY_BACKSPACE 259

#endif
