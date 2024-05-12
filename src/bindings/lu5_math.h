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
