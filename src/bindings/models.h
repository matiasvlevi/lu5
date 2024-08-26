#ifndef _LU5_MODELS_BINDINGS_
#define _LU5_MODELS_BINDINGS_

#include <lua.h>

/**
 * Draw a 3D model
 * 
 * @param model The 3D model
 *
 */
int model(lua_State *L);

/**
 * Load a 3D model
 * 
 * @param model The 3D model
 *
 */
int loadModel(lua_State *L);

#endif /* _LU5_MODELS_BINDINGS_ */