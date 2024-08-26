#include "lu5_print.h"

#include <stdio.h>
#include <lauxlib.h>
#include "lu5_logger.h"

int lu5_get_length(lua_State *L, int index) 
{	
	int count = 0;
	
	lua_pushnil(L);

	while (lua_next(L, index) != 0) {
		lua_pop(L, 1);

		count++;
	}

	return count;
}

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
			printf("\x1b[34m[lua function]\x1b[0m%c", sep);
			break;
		}
		case LUA_TNUMBER:{
			if (lua_isinteger(L, index)) {
				lua_Integer value = lua_tointeger(L, index);
				printf("\x1b[33m%i\x1b[0m%c", value, sep);
			} else {
				lua_Number value = lua_tonumber(L, index);
				printf("\x1b[33m%f\x1b[0m%c", value, sep);
			}
			break;
		}
		case LUA_TSTRING: {
			str = lua_tostring(L, index);
			if (str == NULL) {
				printf("(nil str)");
				return;
			}

			if (nested > 0) {
				printf("\x1b[32m\'%s\'\x1b[0m%c", str, sep);
			} else {
				printf("%s%c", str, sep);
			}
			break;
		}
		case LUA_TTABLE: {
			// If implements the print method,
			// run it
			int has_metatable = lua_getmetatable(L, index);
			if (has_metatable) {
				lua_getfield(L, -1, "print");
				if (lua_isfunction(L, -1)) {

					lua_pushvalue(L, index);

					if (lua_pcall(L, 1, 0, 0) != LUA_OK) {
						luaL_error(L, lua_tostring(L, -1));
						lua_pop(L, 1);
					}
					
					lua_pop(L, 1);
					break;
				} else {

					// else print as table
					lu5_print_list(L, index, nested, sep);

					lua_pop(L, 2);
					break;
				}
			}

			// else print as table
			lu5_print_list(L, index, nested, sep);
			break;
		}
		case LUA_TLIGHTUSERDATA: {
			void *ptr = lua_touserdata(L, index);
			if (ptr != NULL) {
				printf("\x1b[35m[ptr: %p]\x1b[0m%c", ptr, sep);
			} else {
				printf("Error: Null light userdata\n");
			}
			break;
		}
		case LUA_TUSERDATA: {
			// If implements the print method,
			// run it
			int has_metatable = lua_getmetatable(L, index);
			if (has_metatable) {
				lua_getfield(L, -1, "__methods");
				lua_getfield(L, -1, "print");
				if (lua_isfunction(L, -1)) {
					
					lua_pushvalue(L, index);
					
					if (lua_pcall(L, 1, 0, 0) != LUA_OK) {
						luaL_error(L, lua_tostring(L, -1));
						lua_pop(L, 1);
					}
					lua_pop(L, 2);
					break;
				} else {
					lu5_print_list(L, index, nested, sep);
					
					lua_pop(L, 2);
					break;
				}
			} else {
				luaL_error(L, "Does not contain metatable");
				break;
			}
		}
		// TODO: Handle these
		case LUA_TTHREAD: 
		default: {
			const char* typename = lua_typename(L, type);
			
			printf("[unknown %s]%c", typename, sep);
			break;
		}
	}
}
 
void lu5_print_list(lua_State *L, int index, int depth, char sep) 
{
	// Placeholder to avoid infinite recursion
	if (depth > PRINT_DEPTH) {  
		int elem_length = luaL_len(L, index);
		printf("{ \x1b[90m... %i elements\x1b[0m }%c", elem_length+1, sep);
		return;
	}

	// first key
	lua_pushnil(L);

	// Get length
	int len = lu5_get_length(L, index);
	int i = 1;
	
	putchar('{');
	if (len > PRINT_LIST_BREAK) putchar('\n');

	while (lua_next(L, index) != 0) 
	{
		if (lua_gettop(L) < 2) {
			LU5_ERROR("Lua stack does not have enough elements\n");
			lua_pop(L, lua_gettop(L));
			return;
		}
		putchar(' ');

		// key -2
		// value -1

		// Print Key
		if (lua_type(L, -2) == LUA_TSTRING) {
			const char *str = lua_tostring(L, -2);
			
			printf("%s=", str);
		}

		// Print Value

		lu5_print_any(L, lua_gettop(L), depth + 1, (i != len) ? ',' : ' ');

		if (len > PRINT_LIST_BREAK) putchar('\n');

		lua_pop(L, 1);
		i++;
	}
	putchar('}');
	putchar(sep);
}


