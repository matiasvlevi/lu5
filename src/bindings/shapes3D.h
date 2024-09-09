#ifndef _LU5_SHAPES3D_H_
#define _LU5_SHAPES3D_H_
/**
 * @module 3D Shapes
 */
#include <lua.h>

/**
 * Draw a plane.
 * 
 * @param w The width dimension 
 * @param h The height dimension
 *
 * @example
 * function setup()
 *   createWindow(800, 800, GL3D);
 * end
 *
 * function draw()
 *   background(51);
 *  
 *   rotateX(90);
 *   plane(400, 400);
 * end
 *
 * @example
 */
int plane(lua_State *L);

/**
 * Draw a 3D box.
 * 
 * @param w The width dimension 
 * @param [h] The height dimension
 * @param [d] The depth dimension
 *
 * @example
 * function setup()
 *   createWindow(800, 800, GL3D);
 * end
 *
 * function draw()
 *   background(51);
 *  
 *   box(50, 25, 80);
 * end
 *
 * @example
 */
int box(lua_State *L);

/**
 * Draw a 3D Sphere.
 * 
 * @param w The width dimension 
 * @param [detailX] The detail in the X axis
 * @param [detailY] the detailt in the Y axis
 *
 * @example
 * function setup()
 *   createWindow(800, 800, GL3D);
 * end
 *
 * function draw()
 *   background(51);
 *  
 *   sphere(50);
 * end
 * @example
 */
int sphere(lua_State *L);

/**
 * Draw a 3D Cylinder.
 * 
 * @param radius radius of the cylinder. Defaults to 50.
 * @param height height of the cylinder. Defaults to the value of radius.
 * @param detailX number of horizontal edges. Defaults to 24.
 * @param detailY number of subdivisions along the y-axis. Defaults to 1.
 * @param bottomCap whether to draw the cylinder's bottom. Defaults to true.
 * @param topCap whether to draw the cylinder's top. Defaults to true.
 *
 * @example
 * function setup()
 *   createWindow(800, 800, GL3D);
 * end
 *
 * function draw()
 *   background(51);
 *  
 *   cylinder(30, 50);
 * end
 * @example
 */
int cylinder(lua_State *L);


#endif /* _LU5_SHAPES3D_H_ */