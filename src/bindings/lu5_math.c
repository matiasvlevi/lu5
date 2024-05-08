#include "lu5_math.h"
#include "lauxlib.h"
#include <math.h>

int lu5_random(lua_State *L) {
	luaL_error(L, "random not implemented");
	return 1;
}

int lu5_round(lua_State *L) {
	double value = lua_tonumber(L, 1);

	lua_pushinteger(L, round(value));
	return 1;
}

int lu5_floor(lua_State *L) {
	double value = lua_tonumber(L, 1);

	lua_pushinteger(L, floor(value));
	return 1;
}

int lu5_ceil(lua_State *L) {
	double value = lua_tonumber(L, 1);

	lua_pushinteger(L, ceil(value));
	return 1;
}

int lu5_sin(lua_State *L) {
	double value = lua_tonumber(L, 1);

	lua_pushnumber(L, sin(value));
	return 1;
}

int lu5_cos(lua_State *L) {
	double value = lua_tonumber(L, 1);

	lua_pushnumber(L, cos(value));
	return 1;
}

int lu5_tan(lua_State *L) {
	double value = lua_tonumber(L, 1);

	lua_pushnumber(L, tan(value));
	return 1;
}
