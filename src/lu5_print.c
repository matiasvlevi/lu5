#include "lu5_print.h"

#include <lauxlib.h>
#include <stdio.h>

#include "lu5_logger.h"

void lu5_print_any(lua_State *L, int index, int nested, char sep) 
{
	int type = lua_type(L, index);

	const char *str = NULL;

	switch(type) {
		case LUA_TNIL:{
			printf("\x1b[33mnil\x1b[0m%c", sep);
			break;
		}
		case LUA_TBOOLEAN: { 
			int value = lua_toboolean(L, index);
			printf("\x1b[33m%s\x1b[0m%c", value ? "true" : "false", sep);
			break;
		}
		case LUA_TFUNCTION:{
			printf("\x1b[34m[lua function]%c\x1b[0m", sep);
			break;
		}
		case LUA_TNUMBER:{
			if (lua_isinteger(L, index)) {
				int value = lua_tointeger(L, index);
				printf("\x1b[33m%i\x1b[0m%c", value, sep);
			} else {
				double value = lua_tonumber(L, index);
				printf("\x1b[33m%.12lf\x1b[0m%c", value, sep);
			}
			break;
		}
		case LUA_TSTRING: {
			str = lua_tostring(L, index);
			if (str == NULL) return;

			if (nested > 0) {
				printf("\x1b[32m\'%s\'\x1b[0m%c", str, sep);
			} else {
				printf("%s%c", str, sep);
			}
			break;
		}
		case LUA_TTABLE: {
			lu5_print_list(L, index, nested, sep);
			break;
		}
		case LUA_TLIGHTUSERDATA:
			if (lua_islightuserdata(L, index)) {
				void* ptr = lua_touserdata(L, index);

				printf("\x1b[35m[ptr: %p]\x1b[0m%c", ptr, sep);
			}
			break;

		// TODO: Handle these
		case LUA_TUSERDATA:
		case LUA_TTHREAD: 
		default:
			const char* typename = lua_typename(L, type);
			printf("[unknown %s]%c", typename, sep);
			break;
	}
}
 
void lu5_print_list(lua_State *L, int index, int depth, char sep) {

	// Placeholder to avoid infinite recursion
	if (depth > PRINT_DEPTH) {  
		int elem_length = luaL_len(L, index);
		printf("{ \x1b[90m... %i elements\x1b[0m }%c", elem_length, sep);
		return;
	}

	// first key
	lua_pushnil(L);

	// Get length
	int len = lua_rawlen(L, -2);
	int i = 1;

	putchar('{');
	while (lua_next(L, -2) != 0) 
	{
		putchar(' ');
		lu5_print_any(L, -1, depth+1, (i != len) ? ',' : ' ');

		// Remove value, keep key for next iteration
		lua_pop(L, 1);

		i++;
	}
	putchar('}');
	putchar(sep);
}


