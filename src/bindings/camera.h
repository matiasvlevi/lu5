#ifndef _LU5_CAMERA_BINDINGS_
#define _LU5_CAMERA_BINDINGS_

#include <lua.h>

/**
 * Helpful utility for controlling the camera around the origin.
 *
 * Enables quick camera controls without much of an implementation.
 * 
 * @example
 * function setup()
 *     createWindow(800, 800, GL3D);
 * end
 * 
 * function draw() 
 *     background(51);
 * 
 *     -- Allows us to control the camera
 *     orbitControl();
 * 
 *     noFill();
 *     stroke(80, 255, 50);
 *     strokeWeight(4);
 * 
 *     box(60);
 * end
 * @example
 */
int orbitControl(lua_State *L);

#endif /* _LU5_CAMERA_BINDINGS_ */