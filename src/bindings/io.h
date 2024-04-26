#ifndef __LU5_IO_BINDINGS__
#define __LU5_IO_BINDINGS__

#include <lua.h>

/**
 * Flexible printing utility, can take any type, and any number of arguments.
 *
 * @param value The value to print to stdout
 */ 
int print(lua_State *L);

#endif
