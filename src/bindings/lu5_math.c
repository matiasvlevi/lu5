#include "lu5_math.h"
#include "lu5_vector.h"


#include "../lu5_error.h"
#include "../lu5_bindings.h"
#include "../lu5_types.h"

#include <lauxlib.h>
#include <float.h>

int lu5_round(lua_State *L) 
{
	lua_Number value = lu5_assert_number(L, 1, "round");

	lua_pushinteger(L, round(value));
	return 1;
}

int lu5_floor(lua_State *L)
{
	lua_Number value = lu5_assert_number(L, 1, "floor");

	lua_pushinteger(L, floor(value));
	return 1;
}

int lu5_ceil(lua_State *L)
{
	lua_Number value = lu5_assert_number(L, 1, "ceil");

	lua_pushinteger(L, ceil(value));
	return 1;
}

int lu5_abs(lua_State *L)
{
	lua_Number x = lu5_assert_number(L, 1, "abs");

	lua_pushnumber(L, fabs(x));
	return 1;
}

int lu5_map(lua_State *L)
{
	lua_Number x  = lu5_assert_number(L, 1, "map");
	lua_Number s1 = lu5_assert_number(L, 2, "map");
	lua_Number e1 = lu5_assert_number(L, 3, "map");
	lua_Number s2 = lu5_assert_number(L, 4, "map");
	lua_Number e2 = lu5_assert_number(L, 5, "map");

	lua_Number bottom = (e1 - s1);

	lua_Number ratio = 0.0;
	if (bottom != 0.0) ratio = (x - s1) / bottom;

	lua_pushnumber(L, ((e2 - s2) * ratio) + s2);

	return 1;
}

int lu5_dist(lua_State *L)
{
	int argc = lua_gettop(L);

	switch (argc) {
		case 2: {
			lu5_vector_dist(L);
			break;
		}
		case 4: {
			lua_Number x1 = lu5_assert_number(L, 1, "dist");
			lua_Number y1 = lu5_assert_number(L, 2, "dist");
			lua_Number x2 = lu5_assert_number(L, 3, "dist");
			lua_Number y2 = lu5_assert_number(L, 4, "dist");

			lua_Number value = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
			
			lua_pushnumber(L, value);

			break;
		}
		case 6: {
			lua_Number x1 = lu5_assert_number(L, 1, "dist");
			lua_Number y1 = lu5_assert_number(L, 2, "dist");
			lua_Number z1 = lu5_assert_number(L, 3, "dist");
			lua_Number x2 = lu5_assert_number(L, 4, "dist");
			lua_Number y2 = lu5_assert_number(L, 5, "dist");
			lua_Number z2 = lu5_assert_number(L, 6, "dist");

			lua_Number value = sqrt(
				pow(x2 - x1, 2) +  
				pow(y2 - y1, 2) +
				pow(z2 - z1, 2)
			);
			
			lua_pushnumber(L, value);

			break;
		}
	}


	return 1;
}

int lu5_constrain(lua_State *L)
{
	lua_Number x   = lu5_assert_number(L, 1, "constrain");
	lua_Number min = lu5_assert_number(L, 2, "constrain");
	lua_Number max = lu5_assert_number(L, 3, "constrain");
	
	lua_pushnumber(L, fmax(fmin(x, max), min));
	return 1;
}

int lu5_sin(lua_State *L)
{
	lua_Number value = lu5_assert_number(L, 1, "sin");

	lua_pushnumber(L, sin(value));
	return 1;
}

int lu5_cos(lua_State *L)
{
	lua_Number value = lu5_assert_number(L, 1, "cos");

	lua_pushnumber(L, cos(value));
	return 1;
}

int lu5_tan(lua_State *L)
{
	lua_Number value = lu5_assert_number(L, 1, "tan");

	lua_pushnumber(L, tan(value));
	return 1;
}

int lu5_randomSeed(lua_State *L) 
{
	LU5_ONE_TO_ONE_BINDING("math", "randomseed", 0);
	return 0;
}

int lu5_random(lua_State *L) 
{
	int argc = lua_gettop(L);

	// Push a random value on the stack
	lua_getglobal(L, "math");
	lua_getfield(L, -1, "random");
	lua_call(L, 0, 1);

	switch(argc) {
		// Return random value as is
		case 0: return 1;

		// Handle one argument
		case 1: {
			// Get the random value
			lua_Number value = lua_tonumber(L, -1);

			// Handle table
			if (lua_istable(L, 1)) 
			{
				int len = lua_rawlen(L, 1);

				// Map random value to index
				lua_pushnumber(L, ceilf(len * value));
				
				// Return element at index
				lua_gettable(L, 1);
				return 1;
			}			
			// Handle number as scalar range
			else
			{
				// Get arguments
				lua_Number scalar = lu5_assert_number(L, 1, "random");

				// Scale random value
				lua_pushnumber(L, scalar * value);
				return 1;
			}
		}

		// Handle min/max range
		case 2: {
			// Get random value
			lua_Number value = lua_tonumber(L, -1);

			if (lua_isinteger(L, 1) && lua_isinteger(L, 2)) {
				lua_Integer min = lu5_assert_integer(L, 1, "random");
				lua_Integer max = lu5_assert_integer(L, 2, "random");

				lua_pushnumber(L, ceilf(value * (max - min) + min));
			} else {
				// Get arguments
				lua_Number min = lu5_assert_number(L, 1, "random");
				lua_Number max = lu5_assert_number(L, 2, "random");
				
				// Map in range
				lua_pushnumber(L, value * (max - min) + min);
			}

			return 1;

		}

		default: {
			lua_pop(L, 1);
			luaL_error(L, "random expected 0 to 2 arguments, got %i", argc);
			return 0;
		}
	}
}

int lu5_min(lua_State *L)
{	
	lua_Number result = DBL_MAX;

	int argc = lua_gettop(L);
	
	if (argc >= 2) 
	{
		// Iterate over arguments
		for (int i = 1; i <= argc; i++) {
			result = fmin(
				result, 
				lu5_assert_number(L, i, "min")
			);
		}
	} 
	else if (argc == 1 && lua_istable(L, 1)) 
	{
		// Iterate lua table
		lua_pushnil(L);
		while (lua_next(L, 1) != 0) {
			result = fmin(result, lu5_assert_number(L, -1, "min"));

			lua_pop(L, 1);
		}
	} else {
		luaL_error(L, "Expected 2 or more arguments for 'min'");
		return 0;
	}

	lua_pushnumber(L, result);
	return 1;
}

int lu5_max(lua_State *L)
{	
	lua_Number result = DBL_MIN;

	int argc = lua_gettop(L);
	
	if (argc >= 2) 
	{
		// Iterate over arguments
		for (int i = 1; i <= argc; i++) {
			result = fmax(
				result, 
				lu5_assert_number(L, i, "max")
			);
		}
	} 
	else if (argc == 1 && lua_istable(L, 1)) 
	{
		// Iterate lua table
		lua_pushnil(L);
		while (lua_next(L, 1) != 0) {
			result = fmax(result, lu5_assert_number(L, -1, "max"));

			lua_pop(L, 1);
		}
	} else {
		luaL_error(L, "Expected 2 or more arguments for 'max'");

		return 0;
	}

	lua_pushnumber(L, result);
	return 1;
}