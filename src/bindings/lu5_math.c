#include "lu5_math.h"
#include "lauxlib.h"
#include <math.h>

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

	if (x < min) x = min;
	if (x > max) x = max;
	
	lua_pushnumber(L, x);
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
