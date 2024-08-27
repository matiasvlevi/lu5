#ifndef _LU5_CAMERA_BINDINGS_
#define _LU5_CAMERA_BINDINGS_

#include <lua.h>
#include <stdbool.h>

typedef struct lu5_orbit_s {
	bool dragging;

	float radius;
	
    float camera_angle_y;
	float camera_angle_x;
	
    float angular_velocity_y;
	float angular_velocity_x;
	
    float previous_mouse_x;
	float previous_mouse_y;
} lu5_orbit;

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