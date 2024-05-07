#ifndef _LU5_MATH_H_
#define _LU5_MATH_H_

#include <lua.h>

int lu5_random(lua_State *L);

/**
 * Round a number to the nearest integer
 * 
 * @param x The value to round
 *
 * @return int The rounded value
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

#endif
