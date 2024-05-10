#ifndef _LU5_LOADERS_H_
#define _LU5_LOADERS_H_

#include <lua.h>

/**
 * Load a font face
 * 
 * @param path The font path on the local system
 * 
 * @example
 * function setup()
 *   createWindow(600, 600);
 *   myfont = loadFont('/path/to/myfont.ttf');
 * end
 *
 * function draw()
 *   background(51);
 *
 *   textFont(myfont);
 *   text('Hello from lu5!', 30, 50);
 * end   
 * @example
 *
 * @return font The image reference
 */
int loadFont(lua_State *L);

/**
 * Load a png or jpeg image 
 * 
 * @param path The local image path
 * 
 * @example
 * function setup()
 *   createWindow(600, 600);
 *   img = loadImage('/path/to/mypic.png');
 * end
 *
 * function draw()
 *   background(51);
 *
 *   image(img, 0, 0);
 * end   
 * @example
 *
 * @return image The image reference
 */
int loadImage(lua_State *L);

int loadJSON(lua_State *L);

int loadCSV(lua_State *L);

int loadText(lua_State *L);

#endif
