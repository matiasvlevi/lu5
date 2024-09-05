#ifndef _LU5_MATH_H_
#define _LU5_MATH_H_

#include <lua.h>
#include <math.h>

/**
 * Set a random seed
 * 
 * @param seed The seed value
 * 
 * This is a one to one binding of `math.randomseed`
 *
 * @return number The random value 
 */
int lu5_randomSeed(lua_State *L);

/**
 * Get a random number
 * 
 * @param max The maximum of the range
 *
 * @call
 * @param min The minimum of the range
 * @param max The maximum of the range
 *
 * @call
 * @param arr The array to randomly select an item from
 * 
 * @example 1
 * random()      -- random number between 0 and 1
 * random(3)     -- random number between 0 and 3
 * @example
 *
 * @example 2
 * random(3, 12) -- random number between 3 and 12
 * @example
 *
 * @example 3
 * random({ 'A', 'B', 'C' }) -- random element in table
 * @example
 *
 * @return number The random value 
 */
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
 * Return the smallest value.
 * Can also take any number of arguments, or a table.
 * 
 * @param a The first value
 * @param b The second value
 *
 * @example
 * min(6, 7); -- returns 6
 *
 * min(6, 7, 4); -- returns 4
 *
 * min({ 6, 7, 4 }); -- returns 4
 * @example
 *
 * @return number The smallest value 
 */
int lu5_min(lua_State *L);

/**
 * Return the largest value.
 * Can also take any number of arguments, or a table.
 * 
 * @param a The first value
 * @param b The second value
 *
 * @example
 * max(2, 5); -- returns 5
 *
 * max(2, 5, 7); -- returns 7
 *
 * max({ 2, 5, 7 }); -- returns 7
 * @example
 *
 * @return number The largest value 
 */
int lu5_max(lua_State *L);

/**
 * Returns the absolute value of x
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
 * @param value The value to map
 * @param start The start of the initial range
 * @param end The end of the initial range
 * @param target_start The start of the target range
 * @param target_end The end of the target range
 *
 * @example
 * local mouseX_mapped = map(mouseX, 0, width, 0, 100);
 * -- mapped mouseX between 0 and 100
 * @example
 *
 * @return number The mapped value
 */
int lu5_map(lua_State *L);


/**
 * Calculates the distance between 2 points in 2D or 3D space
 *
 * @param x1 The x coordinate of the first point
 * @param y1 The y coordinate of the first point
 * @param x2 The x coordinate of the second point
 * @param y2 The y coordinate of the second point
 *
 * @call
 * @param x1 The x coordinate of the first point
 * @param y1 The y coordinate of the first point
 * @param z1 The z coordinate of the first point
 * @param x2 The x coordinate of the second point
 * @param y2 The y coordinate of the second point
 * @param z2 The z coordinate of the second point
 *
 * @call
 * @param v1 The first vector
 * @param v2 The second vector
 *
 * @example 1
 * local d = dist(0, 0, 3, 4);
 * print(d) -- 5
 * @example
 *
 * @example 2
 * local d = dist(0, 0, 0, 2, 3, 6);
 * print(d) -- 7
 * @example
 *
 * @example 3
 * local a = createVector(-1, -1);
 * local b = createVector( 2,  3);
 *
 * local d = dist(a, b);
 * print(d) -- 5
 * @example
 *
 * @return number The distance between the points
 */
int lu5_dist(lua_State *L);

/**
 * Limits x to a minimum and maximum value
 *
 * @param x The input value
 * @param min The minimum value
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
 * @constant
 */
#define LU5_PI M_PI

/**
 * @brief TWO_PI
 * @constant
 */
#define LU5_TWO_PI (2*LU5_PI)

/**
 * @brief HALF_PI
 * @constant
 */
#define LU5_HALF_PI (0.5*LU5_PI)

/**
 * @brief QUARTER_PI
 * @constant
 *
 */
#define LU5_QUARTER_PI (0.25*LU5_PI)



#endif
