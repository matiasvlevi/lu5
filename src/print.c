#include "print.h"

#include <lauxlib.h>
#include <stdio.h>

void print_any(lua_State *L, int index, int nested, char sep) 
{
    // Try to print as table
    if (lua_istable(L, index)) {

        if (nested < PRINT_DEPTH) {
            print_list(L, lua_gettop(L), nested);
            putchar(sep);
        } else {
            int elem_length = luaL_len(L, index);
            int color = 90;
            printf("{ \x1b[%um... %i elements\x1b[0m }%c", color, elem_length, sep);
        }

        return;
    }

    // Try to print as string
    const char *str = lua_tostring(L, index);
    if (str) {

        char color = 37;
        
        if (lua_isnumber(L, index)) {
            color = 36;

            printf("\x1b[%im%s\x1b[0m%c", color, str, sep);
        } else {
            printf("%s%c", str, sep);
        }


        return;
    }
    
    printf("[unknown]%c", sep);
}
 
void print_list(lua_State *L, int index, int nested) {
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
        print_any(L, -1, nested+1, (i != length) ? ',' : ' ');
        
        // Pop the value off the stack to clean up
        lua_pop(L, 1);
    }
    putchar('}');
}


