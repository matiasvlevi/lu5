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
 * if (keyIsDown('a')) then
 *   -- key 'a' is down
 * end
 *
 * -- use a global
 * if (keyIsDown(LEFT_ARROW)) then
 *   -- left arrow is down
 * end
 * @example
 *
 * @return boolean Whether or not the key is down
 */
int keyIsDown(lua_State *L);

/**
 * @brief keyPressed
 * 
 * Called whenever a key is pressed.
 * 
 * @param key The pressed key as a string, is nil if glfw cannot find a name for the key
 * @param keyCode The pressed key as a key code
 *
 * @example
 * function setup()
 *    createWindow(600, 600);
 * end
 * 
 * function draw()
 *    background(51);
 * end
 * 
 * function keyPressed(key, keyCode)
 *    print(key, keyCode)
 * end
 * @example
 *
 */
#define LU5_KEY_PRESSED "keyPressed"

/**
 * @brief keyReleased
 * 
 * Called whenever a key is released.
 *
 * @param key The released key as a string, is nil if glfw cannot find a name for the key
 * @param keyCode The released key as a key code
 *
 */ 
#define LU5_KEY_RELEASED "keyReleased"

/**
 * @brief keyHeld
 * 
 * Called whenever a key is held down.
 *
 * @param key The held key as a string, is nil if glfw cannot find a name for the key
 * @param keyCode The held key as a key code
 *
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
 */
#define LU5_KEY_LEFT_ARROW 263

/**
 * @brief RIGHT_ARROW
 * @global
 */
#define LU5_KEY_RIGHT_ARROW 262

/**
 * @brief KEY_ENTER
 * @global
 */
#define LU5_KEY_ENTER 257

/**
 * @brief KEY_BACKSPACE
 * @global
 */
#define LU5_KEY_BACKSPACE 259

/**
 * @brief KEY_A
 * @global
 */
/**
 * @brief KEY_B
 * @global
 */
/**
 * @brief KEY_C
 * @global
 */
/**
 * @brief KEY_D
 * @global
 */
/**
 * @brief KEY_E
 * @global
 */
/**
 * @brief KEY_F
 * @global
 */
/**
 * @brief KEY_G
 * @global
 */
/**
 * @brief KEY_H
 * @global
 */
/**
 * @brief KEY_I
 * @global
 */
/**
 * @brief KEY_J
 * @global
 */
/**
 * @brief KEY_K
 * @global
 */
/**
 * @brief KEY_L
 * @global
 */
/**
 * @brief KEY_M
 * @global
 */
/**
 * @brief KEY_N
 * @global
 */
/**
 * @brief KEY_O
 * @global
 */
/**
 * @brief KEY_P
 * @global
 */
/**
 * @brief KEY_Q
 * @global
 */
/**
 * @brief KEY_R
 * @global
 */
/**
 * @brief KEY_S
 * @global
 */
/**
 * @brief KEY_T
 * @global
 */
/**
 * @brief KEY_U
 * @global
 */
/**
 * @brief KEY_V
 * @global
 */
/**
 * @brief KEY_W
 * @global
 */
/**
 * @brief KEY_X
 * @global
 */
/**
 * @brief KEY_Y
 * @global
 */
/**
 * @brief KEY_Z
 * @global
 */

#endif
