#ifndef __PRINT_H__
#define __PRINT_H__

#include <lua.h>

#define PRINT_DEPTH 2

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
