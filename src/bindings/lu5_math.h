#ifndef _LU5_MATH_H_
#define _LU5_MATH_H_

#include <lua.h>

// not implemented
int lu5_random(lua_State *L);

/**
 * Round a number to the nearest integer
 * 
 * @param x The value to round
 *
 * @return int The rounded value
 *
 */
int lu5_round(lua_State *L);

/**
 * floor is a function that takes in a number, and returns the greatest integer less or equal to x
 * <a href="https://en.wikipedia.org/wiki/Floor_and_ceiling_functions">see here</a> 
 *
 * @param x The value to floor
 *
 * @return int greatest integer less than or equals to x
 */
int lu5_floor(lua_State *L);

/**
 * ceil is a function that takes in a number, and returns the smallest integer greater or equal to x
 * <a href="https://en.wikipedia.org/wiki/Floor_and_ceiling_functions">see here</a> 
 *
 * @param x The value to floor
 *
 * @return int The floored value
 */
int lu5_ceil(lua_State *L);

/**
 * Returns the absolute value of x which is its distance from 0
 * <a href="https://en.wikipedia.org/wiki/Absolute_value">see here</a> 
 *
 * @param x The input value
 *
 * @return number The absolote value of the input
 */
int lu5_abs(lua_State *L);

/**
 * Maps x from an original range to a target range
 *
 * @param x The value to map
 *
 * @param s1 The start of the initial range
 *
 * @param e1 The end of the initial range
 *
 * @param s2 The start of the target range
 *
 * @param e2 The end of the target range
 *
 * @return number The mapped value
 */
int lu5_map(lua_State *L);

/**
 * Calculates the distance between 2 points in 2D space
 *
 * @param x1 The x coordinate of the first point
 *
 * @param y1 The y coordinate of the first point
 *
 * @param x2 The x coordinate of the second point
 *
 * @param y1 The y coordinate of the second point
 *
 * @return number The distance between the points
 */
int lu5_dist(lua_State *L);

/**
 * Limits x to a minimum and maximum value
 *
 * @param x The input value
 *
 * @param min The minimum value
 *
 * @param max The maximum value
 *
 * @return number The constrained value
 */
int lu5_constrain(lua_State *L);

/**
 * Sine function (Trigonometry) 
 *
 * @param x The input value 
 *
 * @return number The output value
 */
int lu5_sin(lua_State *L);

/**
 * Cosine function (Trigonometry) 
 *
 * @param x The input value 
 *
 * @return number The output value
 */
int lu5_cos(lua_State *L);

/**
 * Tangent function (Trigonometry) 
 *
 * @param x The input value 
 *
 * @return number The output value
 */
int lu5_tan(lua_State *L);

/**
 * @brief PI
 * @global
 */
#define LU5_PI 3.14159265358979323846

/**
 * @brief TWO_PI
 * @global
 */
#define LU5_TWO_PI (2*LU5_PI)

/**
 * @brief HALF_PI
 * @global
 */
#define LU5_HALF_PI (0.5*LU5_PI)

/**
 * @brief QUARTER_PI
 * @global
 *
 */
#define LU5_QUARTER_PI (0.25*LU5_PI)



#endif
