#ifndef __LU5_SHAPE_BINDINGS__
#define __LU5_SHAPE_BINDINGS__
/**
 * @module 2D Shapes
 */
#include <lua.h>
#include <GLFW/glfw3.h>

#include <stdbool.h>

#define LINE_POINT_SEGMENTS 24

/**
 * Draw an ellipse to the opengl context
 * 
 * @param x The x position of the ellipse's center 
 * @param y The y position of the ellipse's center
 * @param w The width diameter of the ellipse
 * @param h The height diameter of the ellipse
 *
 * @example
 * function setup()
 *   createWindow(400, 400);
 * end
 *
 * function draw()
 *   background(51);
 *  
 *   ellipse(200, 200, 64, 72);
 * end
 * @example 
 *
 */ 
int ellipse(lua_State *L);

/**
 * Draw a circle to the opengl context
 * 
 * @param x The x position of the circle's center 
 * @param y The y position of the circle's center
 * @param d The diameter of the circle
 *
 * @example
 * function setup()
 *   createWindow(400, 400);
 * end
 *
 * function draw()
 *   background(51);
 *  
 *   circle(200, 200, 32);
 * end
 * @example 
 *
 */
int circle(lua_State *L);

/**
 * Draw a rectangle to the opengl context
 *
 * @param x The x position of the reactangle's top left corner
 * @param y The y position of the reactangle's top left corner
 * @param w The width
 * @param h The height
 *
 * @example
 * function setup()
 *   createWindow(400, 400);
 * end
 *
 * function draw()
 *   background(51);
 *
 *  -- rectangle near the top-left corner
 *   rect(10, 10, 80, 60); 
 * end
 * @example
 *
 */
int rect(lua_State *L);

/**
 * Draw a square to the opengl context
 * 
 * @param x The x position of the square's top left corner
 * @param y The y position of the square's top left corner
 * @param s The size of the square's sides
 *
 * @example
 * function setup()
 *   createWindow(400, 400);
 * end
 *
 * function draw()
 *   background(51);
 *
 *   -- square near the top-left corner
 *   rect(10, 10, 80);
 * end
 * @example
 *
 */
int square(lua_State *L);

/**
 * Draw a line to the opengl context
 * 
 * @param x1 The x position of the first point
 * @param y1 The y position of the first point
 * @param x2 The x position of the second point
 * @param y2 The y position of the second point
 *
 * @example
 * function setup()
 *   createWindow(400, 400);
 * end
 *
 * function draw()
 *   background(51);
 *
 *   -- diagonal line from top-left to bottom-right
 *   line(0, 0, width, height);
 * end
 * @example
 *
 */
int line(lua_State *L);


/**
 * Draw an arc on the screen
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
 *     createWindow(400, 400);
 * end
 * 
 * function draw()
 *     background(51);
 * 
 *     strokeWeight(12)
 *     stroke(0);
 *
 *     -- 3/4 of a pizza
 *     arc(200, 200, 120, 120, 0, HALF_PI * 3);
 * end
 * @example
 */ 
int arc(lua_State *L);


/**
 * Draw a point on the screen
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
 *     createWindow(400, 400);
 * end
 * 
 * function draw()
 *     background(51);
 * 
 *     strokeWeight(12);
 *     stroke('yellow');
 *
 *     point(mouseX, mouseY);
 * end
 * @example
 */ 
int point(lua_State *L);


/**
 * Draw a quad on the screen
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
 *     createWindow(400, 400);
 * end
 * 
 * function draw()
 *     background(51);
 * 
 *    push();
 *    translate(50, 50);
 *    quad(
 *       0, 0,
 *       0, 60,
 *       60, 70,
 *       50, 10
 *    );
 *    pop();
 * end
 * @example
 */ 
int quad(lua_State *L);

/**
 * Draw a triangle on the screen
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
 *     createWindow(400, 400);
 * end
 * 
 * function draw()
 *     background(51);
 * 
 *     push();
 *     translate(130, 50);
 *
 *     triangle(0,0, 100, 0, 50, 50);
 *     pop();
 * end
 * @example
 */ 
int triangle(lua_State *L);

/**
 * Begin adding vertices to a custom shape
 * 
 * @param mode The opengl shape mode `LINES`, `POINTS`, `QUADS`, `TRIANGLES`, `TRIANGLE_FAN` 
 *
 * The following would draw a 100 by 100 square at position 100, 100
 *
 * @example
 * function setup()
 *   createWindow(400, 400);
 * end
 *
 * function draw()
 *   background(51);
 *  
 *   beginShape(QUADS);
 *     vertex(100, 100);
 *     vertex(100, 200);
 *     vertex(200, 200);
 *     vertex(200, 100);
 *   endShape();
 * end
 * @example
 */
int beginShape(lua_State *L);

/**
 * `beginShape` must be called prior
 * Adding a vertex to a custom shape
 * 
 * @param x The x position
 * @param y The y position
 *
 */
int vertex(lua_State *L);

/**
 * `beginShape` must be called prior
 * Close the custom shape
 *
 */
int endShape(lua_State *L);

#endif
