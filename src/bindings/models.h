#ifndef _LU5_MODELS_BINDINGS_
#define _LU5_MODELS_BINDINGS_

#include <lua.h>

/**
 * Load a 3D model
 * 
 * @param model The 3D model
 *
 * @example
 *
 * function setup()
 *   createWindow(600, 600, GL3D);
 *   
 *   ship = loadModel('path/to/your/ship.obj');
 * end
 *
 * function draw()
 *   background(51);
 *
 *   model(ship);
 * end
 * @example
 */
int loadModel(lua_State *L);

/**
 * Render a 3D model
 * 
 * @param model The 3D model
 *
 */
int model(lua_State *L);

#endif /* _LU5_MODELS_BINDINGS_ */