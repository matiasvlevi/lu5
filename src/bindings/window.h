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
 * Save the current window into an image. Acts as a screenshot.
 *
 * @param path The image path to write to. 
 *
 * In this example, press the mouse to save a screenshot of the window.x
 *
 * @example
 * function setup()
 *   createWindow(300, 300);
 * end
 *
 * function draw()
 *   circle(200, 200, 32);
 *   fill(255, 50, 100);
 *   square(200, 200, 32);
 * end
 *
 * function mousePressed()
 *   saveWindow("./screenshot.png");
 * end
 * @example
 */
int saveWindow(lua_State *L);

/**
 * Set the frame rate.
 * 
 * @param fps The frame rate to set
 *
 * If frame rate is called without an argument, it will return frame per seconds 
 *
 * @visual
 *
 * @example
 * x = 0;
 * r = 16;
 * speed = 50;
 *
 * function setup()
 *   createWindow(200, 200);
 *
 *   frameRate(24); -- Set the frame rate
 * end
 *
 * function draw()
 *   background('purple');
 *   text('fps: ' .. frameRate(), 20, 30);
 *
 *   square(x, 100, r);
 *   if x > width+r then 
 *     x = -r;
 *   else
 *     x = x + speed * deltaTime;
 *   end
 * end
 * @example
 *
 * @example
 * x = 0;
 * r = 16;
 * speed = 50;
 *
 * function setup()
 *   createWindow(200, 200);
 *   frameRate(12);
 * end
 *
 * function draw()
 *   background('purple');
 *   text('fps: ' .. frameRate(), 20, 30);
 *
 *   square(x, 100, r);
 *   if x > width+r then 
 *     x = -r;
 *   else
 *     x = x + speed * deltaTime;
 *   end
 * end
 * @example
 */
int frameRate(lua_State *L);

/**
 * Prevents lu5 from calling `draw` again. <br/>
 *
 * When `noLoop` is called, the draw continues execution, but will not be called again.
 *
 */
int noLoop(lua_State *L);

/**
 * Allow lu5 to call the `draw` function.
 *
 */
int loop(lua_State *L);

/**
 * @brief deltaTime
 * @global 
 *
 * Elapsed time since the last draw call in seconds.
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
 *   background('purple');
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
 * The window's width in pixels. If no window was created, this value is `nil`.
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
 * The window's height in pixels. If no window was created, this value is `nil`.
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
 * Called when the window is resized.
 *
 * @example
 * function setup()
 *     createWindow(500, 500);
 * end
 * 
 * function draw()
 *     background('purple');
 * end
 * 
 * function windowResized()
 *     print('Resized!');
 * end
 * @example
 */ 
#define LU5_WINDOW_RESIZED "windowResized"

#endif
