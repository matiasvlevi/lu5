#include "lu5_print.h"

#include <lauxlib.h>
#include <stdio.h>

void lu5_print_any(lua_State *L, int index, int nested, char sep) 
{
    int type = lua_type(L, index);

    const char *str;

    switch(type) {
        case LUA_TNIL:
            printf("\x1b[33mnil\x1b[0m%c", sep);
            break;

        case LUA_TBOOLEAN: { 
            int value = lua_toboolean(L, index);
            printf("\x1b[33m%s\x1b[0m%c", value ? "true" : "false", sep);
            break;
        }
        case LUA_TFUNCTION:
            printf("\x1b[34m[lua function]\x1b[0m%c", sep);
            break;

        case LUA_TNUMBER:
            str = lua_tostring(L, index);
            if (str != NULL) 
                printf("\x1b[33m%s\x1b[0m%c", str, sep);
            break;

        case LUA_TSTRING: 
            str = lua_tostring(L, index);
            if (str == NULL) return;

            if (nested > 0) {
                printf("\x1b[32m\'%s\'\x1b[0m%c", str, sep);
            } else {
                printf("%s%c", str, sep);
            }
            break;

        case LUA_TTABLE:
            if (!lua_istable(L, index)) {
                return;
            }

            if (nested < PRINT_DEPTH) {
                lu5_print_list(L, lua_gettop(L), nested);
                putchar(sep);
            } else {
                int elem_length = luaL_len(L, index);
                printf("{ \x1b[90m... %i elements\x1b[0m }%c", elem_length, sep);
            }
            break;

        // TODO: Handle these
        case LUA_TUSERDATA: 
        case LUA_TTHREAD: 
        case LUA_TLIGHTUSERDATA:
        default:
            const char* typename = lua_typename(L, type);
            printf("[unknown %s]%c", typename, sep);
            break;
    }
}
 
void lu5_print_list(lua_State *L, int index, int nested) {
    // Get the length of the table
    int length = luaL_len(L, index);

    putchar('{');
    // Iterate through each element of the table
    for (int i = 1; i <= length; i++) {
        // Push the index to the stack
        lua_pushinteger(L, i);
        // Get the value at this index (table is at index 1, pushed index is now at the top)
        lua_gettable(L, index);
        
        // Print value on top of the stack
        putchar(' ');
        lu5_print_any(L, -1, nested+1, (i != length) ? ',' : ' ');
        
        // Pop the value off the stack to clean up
        lua_pop(L, 1);
    }
    putchar('}');
}


