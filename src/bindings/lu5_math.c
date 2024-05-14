#include "lu5_math.h"
#include "lauxlib.h"

#include "../lu5_logger.h"

#include <math.h>
#include <float.h>

int lu5_random(lua_State *L) 
{
	luaL_error(L, "random not implemented");
	return 1;
}

int lu5_round(lua_State *L) 
{
	double value = lua_tonumber(L, 1);

	lua_pushinteger(L, round(value));
	return 1;
}

int lu5_floor(lua_State *L)
{
	double value = lua_tonumber(L, 1);

	lua_pushinteger(L, floor(value));
	return 1;
}

int lu5_ceil(lua_State *L)
{
	double value = lua_tonumber(L, 1);

	lua_pushinteger(L, ceil(value));
	return 1;
}

static double lu5_assert_number(lua_State *L, int index, const char *fname) {
	if (lua_isnumber(L, index)) 
		return lua_tonumber(L, index);

	int type = lua_type(L, index);
	const char* typename = lua_typename(L, type);

	return
		luaL_error(L,  "Expected 'number' in function '%s' at argument %d. Found %s instead.", fname, index, typename);
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

int lu5_abs(lua_State *L)
{
	double x = lua_tonumber(L, 1);

	lua_pushnumber(L, fabs(x));
	return 1;
}

int lu5_map(lua_State *L)
{
	double x = lua_tonumber(L, 1);
	double s1 = lua_tonumber(L, 2);
	double e1 = lua_tonumber(L, 3);
	double s2 = lua_tonumber(L, 4);
	double e2 = lua_tonumber(L, 5);

	double ratio = (x - s1) / (e1 - s1);
	
	lua_pushnumber(L, ((e2 - s2) * ratio) + s2);
	return 1;
}

int lu5_dist(lua_State *L)
{
	double x1 = lua_tonumber(L, 1);
	double y1 = lua_tonumber(L, 2);
	double x2 = lua_tonumber(L, 3);
	double y2 = lua_tonumber(L, 4);

	double value = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
	
	lua_pushnumber(L, value);
	return 1;
}

int lu5_constrain(lua_State *L)
{
	double x = lua_tonumber(L, 1);
	double min = lua_tonumber(L, 2);
	double max = lua_tonumber(L, 3);
	
	lua_pushnumber(L, fmax(fmin(x, max), min));
	return 1;
}

int lu5_sin(lua_State *L)
{
	double value = lua_tonumber(L, 1);

	lua_pushnumber(L, sin(value));
	return 1;
}

int lu5_cos(lua_State *L)
{
	double value = lua_tonumber(L, 1);

	lua_pushnumber(L, cos(value));
	return 1;
}

int lu5_tan(lua_State *L)
{
	double value = lua_tonumber(L, 1);

	lua_pushnumber(L, tan(value));
	return 1;
}
