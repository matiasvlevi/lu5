#ifndef __LU5_SHAPE_BINDINGS__
#define __LU5_SHAPE_BINDINGS__
/**
 * @module 2D Shapes
 */
#include <lua.h>

#ifndef LU5_WASM
#include <GLFW/glfw3.h>
#endif

#include <stdbool.h>

/**
 * Draw a circle on the screen.
 *
 * @visual
 *
 * @param x The x position of the circle's center 
 * @param y The y position of the circle's center
 * @param d The diameter of the circle
 *
 * @example
 * function setup()
 *   createWindow(200, 200);
 * end
 *
 * function draw()
 *   background('purple');
 *  
 *   circle(100, 100, 32);
 * end
 *
 * @example 
 *
 */
int circle(lua_State *L);

/**
 * Draw an ellipse on the screen.
 *
 * @visual
 *
 * @param x The x position of the ellipse's center 
 * @param y The y position of the ellipse's center
 * @param w The width diameter of the ellipse
 * @param h The height diameter of the ellipse
 *
 * @example
 * function setup()
 *   createWindow(200, 200);
 * end
 *
 * function draw()
 *   background('purple');
 *  
 *   ellipse(100, 100, 64, 32);
 * end
 * @example 
 *
 */ 
int ellipse(lua_State *L);

/**
 * Draw a rectangle on the screen.
 *
 * @visual
 *
 * @param x The x position of the rectangle's top left corner
 * @param y The y position of the rectangle's top left corner
 * @param w The width
 * @param h The height
 *
 * @example
 * function setup()
 *   createWindow(200, 200);
 * end
 *
 * function draw()
 *   background('purple');
 *
 *  -- rectangle near the top-left corner
 *   rect(30, 30, 120, 80); 
 * end
 * @example
 */
int rect(lua_State *L);

/**
 * Draw a square on the screen.
 *
 * @visual
 *
 * @param x The x position of the square's top left corner
 * @param y The y position of the square's top left corner
 * @param s The size of the square's sides
 *
 * @example
 * function setup()
 *   createWindow(200, 200);
 * end
 *
 * function draw()
 *   background('purple');
 *
 *   -- square near the top-left corner
 *   rect(30, 20, 64);
 * end
 * @example
 *
 */
int square(lua_State *L);

/**
 * Draw a line on the screen.
 *
 * @visual
 *
 * @param x1 The x position of the first point
 * @param y1 The y position of the first point
 * @param x2 The x position of the second point
 * @param y2 The y position of the second point
 *
 * @example
 * function setup()
 *   createWindow(200, 200);
 * end
 *
 * function draw()
 *   background('purple');
 *   stroke('white');
 *
 *   -- diagonal line from top-left to mouse pointer
 *   line(0, 0, mouseX, mouseY);
 * end
 * @example
 *
 */
int line(lua_State *L);


/**
 * Draw an arc on the screen.
 *
 * @visual
 *
 * @param x The x position of the arc's ellipse
 * @param y The y position of the arc's ellipse
 * @param w The width of the arc's ellipse
 * @param h The height of the arc's ellipse
 * @param start The angle to start the arc
 * @param stop  The angle to stop the arc
 *
 * @example
 * function setup()
 *     createWindow(200, 200);
 * end
 * 
 * function draw()
 *     background('purple');
 *     
 *     local angle = map(mouseX, 0, width, PI, TWO_PI);
 *     arc(100, 100, 64, 64, 0, angle);
 * end
 * @example
 */ 
int arc(lua_State *L);


/**
 * Draw a point on the screen.
 *
 * @visual
 *
 * @param x The point's x coordinate
 * @param y The point's y coordinate
 *
 * Use `stroke` to set the point's color, and use `strokeWeight` to set the point's radius.
 * <br/><br/>
 * Setting the color with `fill` will not affect `point`
 *
 * @example
 * function setup()
 *     createWindow(200, 200);
 * end
 * 
 * function draw()
 *     background('purple');
 * 
 *     strokeWeight(4);
 *     stroke('white');
 *
 *     point(width/2, height/2);
 * end
 * @example
 */ 
int point(lua_State *L);


/**
 * Draw a quad on the screen.
 *
 * @visual
 *
 * @param x1 The x position of the first point
 * @param y1 The y position of the first point
 * @param x2 The x position of the second point
 * @param y2 The y position of the second point
 * @param x3 The x position of the third point
 * @param y3 The y position of the third point
 * @param x4 The x position of the fourth point
 * @param y4 The y position of the fourth point
 *
 * @example
 * function setup()
 *   createWindow(200, 200);
 * end
 *
 * function draw()
 *   background('purple');
 *
 *   quad(30, 60, 160, 50, 130, 165, 40, 145);
 * end
 * @example 
 */ 
int quad(lua_State *L);

/**
 * Draw a triangle on the screen.
 *
 * @visual
 *
 * @param x1 The x position of the first point
 * @param y1 The y position of the first point
 * @param x2 The x position of the second point
 * @param y2 The y position of the second point
 * @param x3 The x position of the third point
 * @param y3 The y position of the third point
 *
 *
 * @example
 * function setup()
 *     createWindow(200, 200);
 * end
 * 
 * function draw()
 *     background('purple');
 * 
 *     triangle(50, 150, 100, 50, 150, 150);
 * end
 * @example
 */ 
int triangle(lua_State *L);

/**
 * Begin adding vertices to a custom shape.
 *
 * @visual
 * 
 * @param [mode] The opengl shape mode `LINES`, `POINTS`, `QUADS`, `TRIANGLES`, `TRIANGLE_FAN` , default is `LINES`
 *
 * The mode param is not completely implemented in lu5-wasm
 *
 * @example
 * function setup()
 *   createWindow(300, 300);
 * end
 *
 * function draw()
 *   background('purple');
 *
 *   beginShape();
 *     vertex(150,  50);
 *     vertex(170, 130);
 *     vertex(250, 130);
 *     vertex(185, 170);
 *     vertex(210, 250);
 *     vertex(150, 200);
 *     vertex( 90, 250);
 *     vertex(115, 170);
 *     vertex( 50, 130);
 *     vertex(130, 130);
 *   endShape();
 * end
 * @example
 */
int beginShape(lua_State *L);

/**
 * Add a vertex to a custom shape.
 * 
 * @param x The x position
 * @param y The y position
 *
 * `beginShape` must be called prior.
 *
 */
int vertex(lua_State *L);

/**
 * Close the custom shape.
 *
 * `beginShape` must be called prior.
 */
int endShape(lua_State *L);

#endif
