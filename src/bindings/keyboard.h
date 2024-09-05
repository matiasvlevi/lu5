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
 * @example
 * function setup()
 *    createWindow(600, 600);
 * end
 * 
 * function draw()
 *    background(51);
 * end
 * 
 * function keyReleased(key, keyCode)
 *    print(key, keyCode)
 * end
 * @example
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
 * @example
 * function setup()
 *    createWindow(600, 600);
 * end
 * 
 * function draw()
 *    background(51);
 * end
 * 
 * function keyHeld(key, keyCode)
 *    print(key, keyCode)
 * end
 * @example
 */ 
#define LU5_KEY_HELD "keyHeld"

/**
 * @brief UP_ARROW
 * @constant
 * 
 */
#define LU5_KEY_UP_ARROW 265

/**
 * @brief DOWN_ARROW
 * @constant
 * 
 */
#define LU5_KEY_DOWN_ARROW 264

/**
 * @brief LEFT_ARROW
 * @constant
 */
#define LU5_KEY_LEFT_ARROW 263

/**
 * @brief RIGHT_ARROW
 * @constant
 */
#define LU5_KEY_RIGHT_ARROW 262

/**
 * @brief KEY_ENTER
 * @constant
 */
#define LU5_KEY_ENTER 257

/**
 * @brief KEY_BACKSPACE
 * @constant
 */
#define LU5_KEY_BACKSPACE 259

/**
 * @brief KEY_A
 * @constant
 */
/**
 * @brief KEY_B
 * @constant
 */
/**
 * @brief KEY_C
 * @constant
 */
/**
 * @brief KEY_D
 * @constant
 */
/**
 * @brief KEY_E
 * @constant
 */
/**
 * @brief KEY_F
 * @constant
 */
/**
 * @brief KEY_G
 * @constant
 */
/**
 * @brief KEY_H
 * @constant
 */
/**
 * @brief KEY_I
 * @constant
 */
/**
 * @brief KEY_J
 * @constant
 */
/**
 * @brief KEY_K
 * @constant
 */
/**
 * @brief KEY_L
 * @constant
 */
/**
 * @brief KEY_M
 * @constant
 */
/**
 * @brief KEY_N
 * @constant
 */
/**
 * @brief KEY_O
 * @constant
 */
/**
 * @brief KEY_P
 * @constant
 */
/**
 * @brief KEY_Q
 * @constant
 */
/**
 * @brief KEY_R
 * @constant
 */
/**
 * @brief KEY_S
 * @constant
 */
/**
 * @brief KEY_T
 * @constant
 */
/**
 * @brief KEY_U
 * @constant
 */
/**
 * @brief KEY_V
 * @constant
 */
/**
 * @brief KEY_W
 * @constant
 */
/**
 * @brief KEY_X
 * @constant
 */
/**
 * @brief KEY_Y
 * @constant
 */
/**
 * @brief KEY_Z
 * @constant
 */

#endif
