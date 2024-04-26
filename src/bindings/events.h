#ifndef __LU5_EVENTS_BINDINGS__
#define __LU5_EVENTS_BINDINGS__

#include <lua.h>

/**
 * Check if a keyboard key is pressed, returns true if key is down and returns false if it's not
 * 
 * @param k The keyboard key to check
 */ 
int isKeyDown(lua_State *L);

#endif
