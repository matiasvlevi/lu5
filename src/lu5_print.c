#include "lu5_print.h"
#include <lauxlib.h>
#include <stdio.h>

#include "lu5_logger.h"

void lu5_print_any(lua_State *L, int index, int nested, char sep) 
{
    int type = lua_type(L, index);
    //LU5_INFO("INDEX: %i, TYPE: %i", index, type);

    // LU5_INFO("LUA_TNIL: %i", LUA_TNIL);
    // LU5_INFO("LUA_TBOOLEAN: %i", LUA_TBOOLEAN);
    // LU5_INFO("LUA_TFUNCTION: %i", LUA_TFUNCTION);
    // LU5_INFO("LUA_TNUMBER: %i", LUA_TNUMBER);
    // LU5_INFO("LUA_TSTRING: %i", LUA_TSTRING);
    // LU5_INFO("LUA_TTABLE: %i", LUA_TTABLE);
    // LU5_INFO("LUA_TUSERDATA: %i", LUA_TUSERDATA);
    // LU5_INFO("LUA_TTHREAD: %i", LUA_TTHREAD);
    // LU5_INFO("LUA_TLIGHTUSERDATA: %i", LUA_TLIGHTUSERDATA);

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
        // TODO: Handle these
        case LUA_TUSERDATA: 
        case LUA_TTHREAD: 
        case LUA_TLIGHTUSERDATA:
        default:
            const char* typename = lua_typename(L, type);
            printf("[unknown %s%c]", typename, sep);
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


