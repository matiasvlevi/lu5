#ifndef _LU5_TYPOGRAPHY_H_
#define _LU5_TYPOGRAPHY_H_

#include <lua.h>

/**
 * Load a font.
 * 
 * @param path The font path on the local system
 *
 * @example
 * function setup()
 *   createWindow(600, 600);
 *   font = loadFont('/path/to/myfont.ttf');
 * end
 *
 * function draw()
 *   background('purple');
 *
 *   textFont(font);
 *   text('Hello from lu5!', 30, 50);
 * end   
 * @example
 *
 * @return font The image reference
 */
int loadFont(lua_State *L);

/**
 * Set a font size.
 *
 * @param size The size of the font in pixels
 *
 * If this is called using fonts, make sure to call `textSize` after calling `textFont`
 *
 * @example
 * textSize(56);
 * text('Big Text', 50, 50);
 * @example
 *
 */
int textSize(lua_State *L);

/**
 * Set a font alignment.
 *
 * @param mode `CENTER`, `LEFT`, `RIGHT`
 *
 * @example
 * textAlign(CENTER);
 * text('Big Text', 50, 50);
 * @example
 *
 */
int textAlign(lua_State *L);

/**
 * Set a font family.
 *
 * @param font The font value returned when using `loadFont`
 *
 * @example
 * textFont(myfont);
 * text('Hello world!', 100, 200);
 * @example
 */ 
int textFont(lua_State *L);

/**
 * Draw text on the screen.
 *
 * @param str String to render
 * @param x The x position of the start of the text
 * @param y The y position of the top of the text
 *
 * Fonts are not yet implemented
 *
 * @example
 * text('Hello lu5!', 40, 60);
 * @example
 */
int text(lua_State *L);

/**
 * @brief CENTER
 * @constant
 *
 * Alignment mode for <a href="./#textAlign">textAlign</a>.
 */
#define LU5_TEXTALIGN_CENTER 1

/**
 * @brief RIGHT
 * @constant
 *
 * Alignment mode for <a href="./#textAlign">textAlign</a>.
 */
#define LU5_TEXTALIGN_RIGHT 2

/**
 * @brief LEFT
 * @constant
 *
 * Alignment mode for <a href="./#textAlign">textAlign</a>.
 */
#define LU5_TEXTALIGN_LEFT 3

#define LU5_TEXTALIGN_MODE_COUNT 3

#endif