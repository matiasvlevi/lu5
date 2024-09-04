#ifndef __LU5_WINDOW_BINDINGS__
#define __LU5_WINDOW_BINDINGS__

#include <lua.h>


/**
 *
 * Create a GLFW window.
 *
 * @param w Window width
 * @param h Window height
 * @param [mode] Rendering mode, either `GL2D` or `GL3D`, by default `GL2D` is set.
 *
 * It is also possible to create a window in the global scope without defining a setup function.
 *
 * @example
 * function setup()
 *   -- Create the window here
 *   createWindow(600, 600);
 * end
 *
 * function draw()
 *   -- draw things
 * end
 * @example
 */ 
int createWindow(lua_State *L);

/**
 * Set the frame rate 
 * 
 * @param fps The frame rate to set
 *
 * If frame rate is called without an argument, it will return frame per seconds 
 *
 * @example
 * x = 0;
 *
 * function setup()
 *   createWindow(400, 400);
 *   frameRate(24);
 * end
 *
 * function draw()
 *   background(51);
 *   text('fps: ' .. frameRate(), 20, 10);
 *
 *   circle(x, 200, 32);
 *   x = x + 1;
 * end
 * @example
 */
int frameRate(lua_State *L);

/**
 * Stop the drawing loop, usefull for fixed image renders 
 */
int noLoop(lua_State *L);

/**
 * Restart the drawing loop
 */
int loop(lua_State *L);

/**
 * @brief deltaTime
 * @global 
 *
 * Elapsed time since the last draw call in seconds
 *
 * @example
 * x = 0;
 * vx = 128;
 *
 * function setup()
 *   createWindow(400, 400);
 *   frameRate(24); -- try with 60
 * end
 *
 * function draw()
 *   background(51);
 *
 *   circle(x, height/2, 32);
 *
 *   -- Get the same velocity with different framerates
 *   x = x + vx * deltaTime;
 * end
 * @example
 */
#define LU5_DELTA_TIME "deltaTime"

/**
 * @brief width
 * @global
 * 
 * The window's width in pixels. If no window was created, this value is `nil`
 *
 * @example
 * createWindow(800, 600);
 *
 * print(width);
 * -- 800
 * @example
 */
#define LU5_WIDTH "width"

/**
 * @brief height
 * @global
 *
 * The window's height in pixels. If no window was created, this value is `nil`
 *
 * @example
 * createWindow(800, 600);
 *
 * print(height);
 * -- 600
 * @example
 */
#define LU5_HEIGHT "height"

/**
 * @brief windowResized
 *
 * Called when the window is resized
 *
 * @example
 * function setup()
 *     createWindow(500, 500);
 * end
 * 
 * function draw()
 *     background(51)
 * end
 * 
 * function windowResized()
 *     print('Resized!')
 * end
 * @example
 */ 
#define LU5_WINDOW_RESIZED "windowResized"

#endif
