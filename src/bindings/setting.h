#ifndef __LU5_SETTING_BINDINGS__
#define __LU5_SETTING_BINDINGS__

#include <lua.h>
#include "../lu5_setting.h"

/**
 * Clear a background with a color. 
 *
 * @param r The red byte
 * @param g The green byte
 * @param b The blue byte
 *
 * @call
 * @param r The red byte
 * @param g The green byte
 * @param b The blue byte
 * @param a The alpha byte
 *
 * @call
 * @param v The grayscale value
 * 
 * @call
 * @param color_name The color name
 *
 * @call
 * @param hex The hex color string
 *
 * @example 1
 *  background(100, 255, 100);
 * @example
 *
 * @example 2
 *  background(100, 255, 100, 150);
 * @example
 *
 * @example 3
 *  background(100);
 * @example
 *
 * @example 4
 *  background('yellow');
 * @example
 *
 * @example 5
 *  background('#88EE66');
 * @example 
 */  
int background(lua_State *L);

/**
 * Set the fill color for shapes. 
 *
 * @param r The red byte
 * @param g The green byte
 * @param b The blue byte
 *
 * @call
 * @param r The red byte
 * @param g The green byte
 * @param b The blue byte
 * @param a The alpha byte
 *
 * @call
 * @param v The grayscale value
 * 
 * @call
 * @param color_name The color name
 *
 * @call
 * @param hex The hex color string
 *
 * @example 1
 *  fill(100, 255, 100);
 * @example
 *
 * @example 2
 *  fill(100, 255, 100, 150);
 * @example
 *
 * @example 3
 *  fill(100);
 * @example
 *
 * @example 4
 *  fill('yellow');
 * @example
 *
 * @example 5
 *  fill('#88EE66');
 * @example 
 */ 
int fill(lua_State *L);

/**
 * Set the line width. 
 *
 * @param weight The line width in pixels
 *
 * @example
 * strokeWeight(8);
 * line(200, 200, mouseX, mouseY);
 * @example
 */
int strokeWeight(lua_State *L);

/**
 * Disable fill. 
 *
 * @example
 * noFill();
 * circle(200, 200, 32);
 * @example
 */
int noFill(lua_State *L);

/**
 * Set the stroke color for shapes
 *
 * @param r The red byte
 * @param g The green byte
 * @param b The blue byte
 *
 * @call
 * @param r The red byte
 * @param g The green byte
 * @param b The blue byte
 * @param a The alpha byte
 *
 * @call
 * @param v The grayscale value
 * 
 * @call
 * @param color_name The color name
 *
 * @example 1
 *  stroke(255, 255, 100);
 * @example
 *
 * @example 2
 *  stroke(255, 255, 100, 150);
 * @example
 *
 * @example 3
 *  stroke(255);
 * @example
 *
 * @example 4
 *  stroke('red');
 * @example
 */ 
int stroke(lua_State *L);

/**
 * Disable stroke. 
 */ 
int noStroke(lua_State *L);

/**
 * Save the style and transformation settings. <br/>
 *
 * Pushes the lu5 style settings off the stack. 
 * Pushes the OpenGL transformation matrix off the stack.
 *
 * @visual
 *
 * @example
 * function setup()
 *     createWindow(400, 400);
 * end
 * 
 * function draw()
 *     background('purple');
 * 
 *     push();
 *     fill(155, 255, 0);
 *     strokeWeight(12);
 * 
 *     -- Affected by style
 *     circle(300, 200, 32);
 *     pop();
 * 
 *     -- Not Affected by style
 *     circle(100, 200, 32);
 * end
 * @example
 * 
 * @example
 * function setup()
 *     createWindow(400, 400);
 * end
 * 
 * function draw()
 *     background('purple');
 * 
 *     push();
 *     fill('red');
 *     translate(200, 200);
 * 
 *     -- Affected by transformation
 *     circle(0, 0, 32);
 *     pop();
 * 
 *     -- Not Affected by transformation
 *     circle(0, 0, 32);
 * end
 * @example
 */
int push(lua_State *L);

/**
 * Restore the style and transformation settings. <br/>
 *
 * Pops the lu5 style settings off the stack. 
 * Pops the OpenGL transformation matrix off the stack.
 */
int pop(lua_State *L);

/**
 * Set rectangle alignment mode.
 *
 * @param mode either `CENTER`, `CORNER`, `RADIUS`
 *
 * @example @live
 * function setup()
 *   createWindow(200, 200);
 *
 *   rectMode(CENTER);
 * end
 *
 * function draw()
 *   background('purple');
 *   
 *   rect(width/2, height/2, 80, 40);
 *   point(width/2, height/2);
 * end
 * @example
 *
 * @example @live
 * function setup()
 *   createWindow(200, 200);
 *
 *   rectMode(CORNER);
 * end
 *
 * function draw()
 *   background('purple');
 *   
 *   rect(width/2, height/2, 80, 40);
 *   point(width/2, height/2);
 * end
 * @example
 *
 * @example @live
 * function setup()
 *   createWindow(200, 200);
 *
 *   rectMode(RADIUS);
 * end
 *
 * function draw()
 *   background('purple');
 *   
 *   rect(width/2, height/2, 80, 40);
 *   point(width/2, height/2);
 * end
 * @example
 */ 
int rectMode(lua_State *L);

/**
 * Toggle a helpful mode with 3D Graphics.
 *
 * @param [enable] Whether or not to enable the debug mode, if not provided, it defaults to `true` 
 *
 * @example
 * function setup()
 *   createWindow(800, 800, GL3D);
 *
 *   debugMode();
 * end
 *
 * function draw()
 *   background('purple');
 *   
 *   box(100);
 * end
 * @example
 *
 * @example
 * function setup()
 *   createWindow(800, 800, GL3D);
 * end
 *
 * function draw()
 *   background('purple');
 *   
 *   -- When the d key is down, show debug graphics
 *   if (keyIsDown('d')) then
 *     debugMode(true);
 *   else
 *     debugMode(false);
 *   end
 *
 *   box(100);
 * end
 * @example
 */
int debugMode(lua_State *L);

#define LU5_RECT_ALIGN_MODE_COUNT 3

/**
 * @brief CENTER
 * @constant
 *
 * Alignment mode for <a href="./#rectMode">rectMode</a>.
 */
#define LU5_RECTMODE_CENTER 1

/**
 * @brief CORNER
 * @constant
 *
 * Alignment mode for <a href="./#rectMode">rectMode</a>.
 */
#define LU5_RECTMODE_CORNER 2

/**
 * @brief RADIUS
 * @constant
 *
 * Alignment mode for <a href="./#rectMode">rectMode</a>.
 */
#define LU5_RECTMODE_RADIUS 3

#endif
