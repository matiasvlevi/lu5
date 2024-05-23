#ifndef _LU5_TYPES_H_
#define _LU5_TYPES_H_

#include <lua.h>

#define LU5_CONCAT(a, b) a ## b
#define LU5_TYPE_BIND_DECLARATION(ctype, luatype)\
	ctype LU5_CONCAT(lu5_assert_, luatype)(lua_State *L, int index, const char *fname);

#define LU5_TYPE_BIND(ctype, luatype)\
	ctype LU5_CONCAT(lu5_assert_, luatype)(lua_State *L, int index, const char *fname)\
	{\
		if (LU5_CONCAT(lua_is, luatype)(L, index))\
			return LU5_CONCAT(lua_to, luatype)(L, index);\
		int type = lua_type(L, index);\
		const char* typename = lua_typename(L, type);\
		luaL_error(L,\
			"Function \x1b[90m'%s'\x1b[0m expected \x1b[90m'%s'\x1b[0m at argument \x1b[33m%d\x1b[0m. Found %s instead.",\
			fname, #luatype, index, typename);\
		return (ctype)(0x00);\
	};

LU5_TYPE_BIND_DECLARATION(double      , number);
LU5_TYPE_BIND_DECLARATION(int         , integer);
LU5_TYPE_BIND_DECLARATION(const char *, string);

#endif