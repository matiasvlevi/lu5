#ifndef __LU5_IO_BINDINGS__
#define __LU5_IO_BINDINGS__

#include <lua.h>

/**
 * Printing utility, can take any lua type (except objects).
 *
 * @param value The value to print to stdout
 */ 
int print(lua_State *L);

#endif
