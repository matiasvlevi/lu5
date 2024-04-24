#include "io.h"

#include "../print.h"

int print(lua_State *L)
{
    int argc = lua_gettop(L);

    // Print all arguments
    for (int i = 0; i < argc-1; i++) {
        print_any(L, i+1, 0, ' ');
    }
    print_any(L, argc, 0, '\n');

    return 0;
}
