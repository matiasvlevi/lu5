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
 * Draw a circle to the opengl context
 * 
 * @param x The x position of the circle's center 
 * @param y The y position of the circle's center
 * @param d The diameter of the circle
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
 */
int rect(lua_State *L);

/**
 * Draw a square to the opengl context
 * 
 * @param x The x position of the square's top left corner
 * @param y The y position of the square's top left corner
 * @param s The size of the square's sides
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
 */
int line(lua_State *L);

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
 */ 
int quad(lua_State *L);

/**
 * Draw a point on the screen
 *
 * @note Not implemented
 *
 */ 
int point(lua_State *L);

/**
 * Draw an arc on the screen
 *
 * @note Not implemented
 *
 */ 
int arc(lua_State *L);

/**
 * Draw an ellipse on the screen
 *  
 * @note Not implemented
 *
 */ 
int ellipse(lua_State *L);

/**
 * Draw a triangle on the screen
 *
 * @note Not implemented
 *
 */ 
int triangle(lua_State *L);

/**
 * Begin adding vertices to a custom shape
 * 
 * @param mode The opengl shape mode `LINES`, `POINTS`, `QUADS`, `TRIANGLES`, `TRIANGLE_FAN` 
 *
 * The following would draw a 100 by 100 square at position 100, 100
 * @example
 * beginShape(QUADS);
 *   vertex(100, 100);
 *   vertex(100, 200);
 *   vertex(200, 200);
 *   vertex(200, 100);
 * endShape();
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
