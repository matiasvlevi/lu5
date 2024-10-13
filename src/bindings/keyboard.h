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
 * @param key The pressed key as a string, is nil if glfw cannot find a name for the key.
 * @param keyCode The pressed key as a key code
 * 
 * @example @live
 * function setup()
 *    createWindow(200, 200);
 *
 *    background('purple');
 *    text('Press any key', 10, 40);
 * end
 * 
 * -- no draw
 * function draw() return end 
 * 
 * function keyPressed(key, keyCode)
 *    print(key, keyCode);
 *
 *    background('purple');
 *
 *    if key ~= nil then 
 *        text('Pressed: ' .. key, 10, 40);
 *    end
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
 * @example @live
 * function setup()
 *    createWindow(200, 200);
 *
 *    background('purple');
 *    text('Release any key', 10, 40);
 * end
 * 
 * -- no draw
 * function draw() return end 
 * 
 * function keyReleased(key, keyCode)
 *    print(key, keyCode);
 *
 *    background('purple');
 *
 *    if key ~= nil then 
 *        text('Released: ' .. key, 10, 40);
 *    end
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
 * @example @live
 * function setup()
 *    createWindow(200, 200);
 *
 *    background('purple');
 *    text('Hold any key', 10, 40);
 * end
 * 
 * -- no draw
 * function draw() return end 
 * 
 * function keyHeld(key, keyCode)
 *    print(key, keyCode);
 *
 *    background('purple');
 *
 *    if key ~= nil then 
 *        text('Held key: ' .. key, 10, 40);
 *    end
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
#ifdef LU5_WASM
    #define LU5_KEY_0 48
    #define LU5_KEY_1 49
    #define LU5_KEY_2 50
    #define LU5_KEY_3 51
    #define LU5_KEY_4 52
    #define LU5_KEY_5 53
    #define LU5_KEY_6 54
    #define LU5_KEY_7 55
    #define LU5_KEY_8 56
    #define LU5_KEY_9 57

    #define LU5_KEY_A 65
    #define LU5_KEY_B 66
    #define LU5_KEY_C 67
    #define LU5_KEY_D 68
    #define LU5_KEY_E 69
    #define LU5_KEY_F 70
    #define LU5_KEY_G 71
    #define LU5_KEY_H 72
    #define LU5_KEY_I 73
    #define LU5_KEY_J 74
    #define LU5_KEY_K 75
    #define LU5_KEY_L 76
    #define LU5_KEY_M 77
    #define LU5_KEY_N 78
    #define LU5_KEY_O 79
    #define LU5_KEY_P 80
    #define LU5_KEY_Q 81
    #define LU5_KEY_R 82
    #define LU5_KEY_S 83
    #define LU5_KEY_T 84
    #define LU5_KEY_U 85
    #define LU5_KEY_V 86
    #define LU5_KEY_W 87
    #define LU5_KEY_X 88
    #define LU5_KEY_Y 89
    #define LU5_KEY_Z 90

    #define LU5_KEY_BACKSLASH 92
    #define LU5_KEY_GRAVE_ACCENT 96
    #define LU5_KEY_ESCAPE 256
    #define LU5_KEY_TAB 258
    #define LU5_KEY_INSERT 260
    #define LU5_KEY_DELETE 261
    #define LU5_KEY_PAGE_UP 266
    #define LU5_KEY_PAGE_DOWN 267
    #define LU5_KEY_HOME 268
    #define LU5_KEY_END 269
    #define LU5_KEY_CAPS_LOCK 280
#else
    #define LU5_KEY_0 GLFW_KEY_0
    #define LU5_KEY_1 GLFW_KEY_1
    #define LU5_KEY_2 GLFW_KEY_2
    #define LU5_KEY_3 GLFW_KEY_3
    #define LU5_KEY_4 GLFW_KEY_4
    #define LU5_KEY_5 GLFW_KEY_5
    #define LU5_KEY_6 GLFW_KEY_6
    #define LU5_KEY_7 GLFW_KEY_7
    #define LU5_KEY_8 GLFW_KEY_8
    #define LU5_KEY_9 GLFW_KEY_9

    #define LU5_KEY_A GLFW_KEY_A
    #define LU5_KEY_B GLFW_KEY_B
    #define LU5_KEY_C GLFW_KEY_C
    #define LU5_KEY_D GLFW_KEY_D
    #define LU5_KEY_E GLFW_KEY_E
    #define LU5_KEY_F GLFW_KEY_F
    #define LU5_KEY_G GLFW_KEY_G
    #define LU5_KEY_H GLFW_KEY_H
    #define LU5_KEY_I GLFW_KEY_I
    #define LU5_KEY_J GLFW_KEY_J
    #define LU5_KEY_K GLFW_KEY_K
    #define LU5_KEY_L GLFW_KEY_L
    #define LU5_KEY_M GLFW_KEY_M
    #define LU5_KEY_N GLFW_KEY_N
    #define LU5_KEY_O GLFW_KEY_O
    #define LU5_KEY_P GLFW_KEY_P
    #define LU5_KEY_Q GLFW_KEY_Q
    #define LU5_KEY_R GLFW_KEY_R
    #define LU5_KEY_S GLFW_KEY_S
    #define LU5_KEY_T GLFW_KEY_T
    #define LU5_KEY_U GLFW_KEY_U
    #define LU5_KEY_V GLFW_KEY_V
    #define LU5_KEY_W GLFW_KEY_W
    #define LU5_KEY_X GLFW_KEY_X
    #define LU5_KEY_Y GLFW_KEY_Y
    #define LU5_KEY_Z GLFW_KEY_Z

    #define LU5_KEY_BACKSLASH GLFW_KEY_BACKSLASH
    #define LU5_KEY_GRAVE_ACCENT GLFW_KEY_GRAVE_ACCENT
    #define LU5_KEY_ESCAPE GLFW_KEY_ESCAPE
    #define LU5_KEY_TAB GLFW_KEY_TAB
    #define LU5_KEY_INSERT GLFW_KEY_INSERT
    #define LU5_KEY_DELETE GLFW_KEY_DELETE
    #define LU5_KEY_PAGE_UP GLFW_KEY_PAGE_UP
    #define LU5_KEY_PAGE_DOWN GLFW_KEY_PAGE_DOWN
    #define LU5_KEY_HOME GLFW_KEY_HOME
    #define LU5_KEY_END GLFW_KEY_END
    #define LU5_KEY_CAPS_LOCK GLFW_KEY_CAPS_LOCK
#endif

#endif
