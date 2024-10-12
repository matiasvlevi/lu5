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
 *   background('purple');
 *
 *   image(img, 0, 0);
 * end   
 * @example
 *
 * @return Image The image instance
 */
int loadImage(lua_State *L);

/**
 * Draw an image to the screen
 * 
 * @param img The Image instance
 * @param x The x position of the image
 * @param y The y position of the image
 * @param [w] The width of the image, if not specified, using source width
 * @param [h] The height of the image, if not specified, using source height
 */
int image(lua_State *L);

/**
 * Crop an Image into an other Image.
 * 
 * @name Image.crop
 *
 * @visual
 * 
 * @param x The x position of the image
 * @param y The y position of the image
 * @param w The width of the new cropped image
 * @param h The height of the new cropped image
 *
 * @example
 * function setup()
 *     createWindow(400, 400);
 * 
 *     img = loadImage('examples/images/cat.jpg');
 * 
 *     cropped = img:crop(150, 150, 125, 200);
 *     -- -- or
 *     -- cropped = Image.crop(img, 150, 150, 125, 200);
 * end
 * 
 * function draw() 
 *     background('purple');
 * 
 *     image(img, 0, 0);
 *     image(cropped, x, y);
 * end
 * @example
 *
 * @return Image the cropped image
 */
int lu5_image_get(lua_State *L);

int lu5_image_index(lua_State *L);

void lu5_image_bind(lua_State *L);

#endif 