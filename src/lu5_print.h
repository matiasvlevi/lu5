#ifndef _LU5_IO_H_
#define _LU5_IO_H_

#include <lua.h>

#define PRINT_LIST_BREAK 3
#define PRINT_DEPTH 3

// TODO: Make these function buffered

/**
 * Print any lua type
 */ 
void lu5_print_any(lua_State *L, int idx, int nested, char sep);
 
/**
 * Print a list
 */ 
void lu5_print_list(lua_State *L, int idx, int nested, char sep);

#endif
