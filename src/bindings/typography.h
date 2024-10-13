#ifndef _LU5_TYPOGRAPHY_H_
#define _LU5_TYPOGRAPHY_H_

#include <lua.h>


/**
 * Draw text on the screen.
 *
 * @param str String to render
 * @param x The x position of the start of the text
 * @param y The y position of the top of the text
 *
 * Fonts are not yet implemented
 *
 * @example @live
 * function setup()
 *   createWindow(200, 200);
 * end
 * 
 * function draw()
 *   background('purple');
 *
 *   text('Hello from lu5!', 25, 110);
 * end
 * @example
 */
int text(lua_State *L);


/**
 * Set a font family.
 *
 * @param font The font value returned when using `loadFont`
 *
 * @example @live
 * function setup()
 *   createWindow(200, 200);
 * end
 * 
 * function draw()
 *   background('purple');
 *
 *   textFont('Monospace');
 *   text('Hello from lu5!', 5, 110);
 * end
 * @example
 */ 
int textFont(lua_State *L);

/**
 * Load a font.
 * 
 * @param path The font path on the local system
 *
 * @example @live
 * -- For Web
 * function setup()
 *   createWindow(200, 200);
 *   -- loadFont is not needed here...
 * end
 *
 * function draw()
 *   background('purple');
 *
 *   textFont('Verdana');
 *   text('Hello from lu5!', 35, 110);
 * end  
 * @example
 *
 * @example
 * -- For native
 * function setup()
 *   createWindow(200, 200);
 *   font = loadFont('/path/to/myfont.ttf');
 * end
 *
 * function draw()
 *   background('purple');
 *
 *   textFont(font);
 *   text('Hello from lu5!', 35, 110);
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
 * @example @live
 * function setup()
 *   createWindow(200, 200);
 * end
 * 
 * function draw()
 *   background('purple');
 *
 *   textSize(48); -- Larger text
 *   text('Hello lu5!', 0, 120);
 * end
 * @example
 *
 */
int textSize(lua_State *L);

/**
 * Set a font alignment.
 *
 * @param mode `CENTER`, `LEFT`, `RIGHT`
 *
 * @example @live
 * function setup()
 *   createWindow(200, 200);
 *   textAlign(CENTER); 
 * end
 * 
 * function draw()
 *   background('purple');
 *
 *   text('Hello lu5!', width/2, height/2);
 *   point(width/2, height/2);
 * end
 * @example
 *
 */
int textAlign(lua_State *L);

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