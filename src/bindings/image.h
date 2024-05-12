#ifndef _LU5_IMAGE_BINDINGS_H_
#define _LU5_IMAGE_BINDINGS_H_

#include <lua.h>

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
 * @return img The image reference
 */
int loadImage(lua_State *L);

/**
 * Draw an image to the screen
 * 
 * @param image The image reference
 * @param x The x position of the image
 * @param y The y position of the image
 * @param [w] The width of the image, if not specified, using source width
 * @param [h] The height of the image, if not specified, using source height
 */
int image(lua_State *L);

#endif 