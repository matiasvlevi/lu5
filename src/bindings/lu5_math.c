#include "lu5_math.h"
#include "lauxlib.h"

#include "../lu5_logger.h"
#include "../lu5_bindings.h"

#include <math.h>
#include <float.h>

static double lu5_assert_number(lua_State *L, int index, const char *fname) {
	if (lua_isnumber(L, index)) 
		return lua_tonumber(L, index);

	int type = lua_type(L, index);
	const char* typename = lua_typename(L, type);

	return
		luaL_error(L, "Function \x1b[90m'%s'\x1b[0m expected \x1b[90m'number'\x1b[0m at argument \x1b[33m%d\x1b[0m. Found %s instead.", fname, index, typename);
}

int lu5_round(lua_State *L) 
{
	double value = lu5_assert_number(L, 1, "round");

	lua_pushinteger(L, round(value));
	return 1;
}

int lu5_floor(lua_State *L)
{
	double value = lu5_assert_number(L, 1, "floor");

	lua_pushinteger(L, floor(value));
	return 1;
}

int lu5_ceil(lua_State *L)
{
	double value = lu5_assert_number(L, 1, "ceil");

	lua_pushinteger(L, ceil(value));
	return 1;
}

int lu5_abs(lua_State *L)
{
	double x = lu5_assert_number(L, 1, "abs");

	lua_pushnumber(L, fabs(x));
	return 1;
}

int lu5_map(lua_State *L)
{
	double x  = lu5_assert_number(L, 1, "map");
	double s1 = lu5_assert_number(L, 2, "map");
	double e1 = lu5_assert_number(L, 3, "map");
	double s2 = lu5_assert_number(L, 4, "map");
	double e2 = lu5_assert_number(L, 5, "map");

	double ratio = (x - s1) / (e1 - s1);
	
	lua_pushnumber(L, ((e2 - s2) * ratio) + s2);
	return 1;
}

int lu5_dist(lua_State *L)
{
	double x1 = lu5_assert_number(L, 1, "dist");
	double y1 = lu5_assert_number(L, 2, "dist");
	double x2 = lu5_assert_number(L, 3, "dist");
	double y2 = lu5_assert_number(L, 4, "dist");

	double value = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
	
	lua_pushnumber(L, value);
	return 1;
}

int lu5_constrain(lua_State *L)
{
	double x   = lu5_assert_number(L, 1, "constrain");
	double min = lu5_assert_number(L, 2, "constrain");
	double max = lu5_assert_number(L, 3, "constrain");
	
	lua_pushnumber(L, fmax(fmin(x, max), min));
	return 1;
}

int lu5_sin(lua_State *L)
{
	double value = lu5_assert_number(L, 1, "sin");

	lua_pushnumber(L, sin(value));
	return 1;
}

int lu5_cos(lua_State *L)
{
	double value = lu5_assert_number(L, 1, "cos");

	lua_pushnumber(L, cos(value));
	return 1;
}

int lu5_tan(lua_State *L)
{
	double value = lu5_assert_number(L, 1, "tan");

	lua_pushnumber(L, tan(value));
	return 1;
}

int lu5_randomSeed(lua_State *L) 
{
	LU5_ONE_TO_ONE_BINDING("math", "randomseed");
	return 1;
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
			double value = lua_tonumber(L, -1);

			// Handle table
			if (lua_istable(L, 1)) 
			{
				int len = lua_rawlen(L, 1);

				// Map random value to index
				lua_pushinteger(L, (int)ceil(len * value));
				
				// Return element at index
				lua_gettable(L, 1);
				return 1;
			}			
			// Handle number as scalar range
			else
			{
				// Get arguments
				double scalar = lu5_assert_number(L, 1, "random");

				// Scale random value
				lua_pushnumber(L, scalar * value);
				return 1;
			}
		}

		// Handle min/max range
		case 2: {
			// Get random value
			double value = lua_tonumber(L, -1);

			// Get arguments
			double min = lu5_assert_number(L, 1, "random");
			double max = lu5_assert_number(L, 2, "random");

			// Map in range
			lua_pushnumber(L, value * (max - min) + min);
			return 1;
		}

		default: {
			luaL_error(L, "random expected 0 to 2 arguments, got %i", argc);
			return 0;
		}
	}
}

int lu5_min(lua_State *L)
{	
	double result = DBL_MAX;

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
		return	
			luaL_error(L, "Expected 2 or more arguments for 'min'");
	}

	lua_pushnumber(L, result);
	return 1;
}

int lu5_max(lua_State *L)
{	
	double result = DBL_MIN;

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
		return	
			luaL_error(L, "Expected 2 or more arguments for 'max'");
	}

	lua_pushnumber(L, result);
	return 1;
}