#ifndef _LU5_SHAPES3D_H_
#define _LU5_SHAPES3D_H_
/**
 * @module 3D Shapes
 */
#include <lua.h>

/**
 * Draw a plane.
 *
 * @visual
 *
 * @param w The width dimension 
 * @param h The height dimension
 *
 * @example
 * function setup()
 *   createWindow(300, 300, GL3D);
 * end
 *
 * function draw()
 *   background('purple');
 *  
 *   plane(400, 400);
 * end
 *
 * @example
 */
int plane(lua_State *L);

/**
 * Draw a 3D box.
 *
 * @visual
 *
 * @param w The width dimension 
 * @param [h] The height dimension
 * @param [d] The depth dimension
 *
 * @example
 * function setup()
 *   createWindow(300, 300, GL3D);
 * end
 *
 * function draw()
 *   background('purple');
 *  
 *   box(150, 225, 180);
 * end
 * @example
 *
 * @example
 * function setup()
 *   createWindow(300, 300, GL3D);
 * end
 *
 * function draw()
 *   background('purple');
 *   
 *   rotateX(45);
 *   rotateZ(45);
 *
 *   box(150, 225, 180);
 * end
 * @example
 */
int box(lua_State *L);

/**
 * Draw a 3D Sphere.
 *
 * @visual
 *
 * @param w The width dimension 
 * @param [detailX] The detail in the X axis
 * @param [detailY] the detailt in the Y axis
 *
 * @example
 * function setup()
 *   createWindow(300, 300, GL3D);
 * end
 *
 * function draw()
 *   background('purple');
 *  
 *   sphere(200);
 * end
 * @example
 */
int sphere(lua_State *L);

/**
 * Draw a 3D Cylinder.
 *
 * @visual
 *
 * @param [radius] radius of the cylinder. Defaults to 50.
 * @param [height] height of the cylinder. Defaults to the value of radius.
 * @param [detailX] number of horizontal edges. Defaults to 24.
 * @param [detailY] number of subdivisions along the y-axis. Defaults to 1.
 * @param [bottomCap] whether to draw the cylinder's bottom. Defaults to true.
 * @param [topCap] whether to draw the cylinder's top. Defaults to true.
 *
 * @example
 * function setup()
 *   createWindow(300, 300, GL3D);
 * end
 *
 * function draw()
 *   background('purple');
 *  
 *   cylinder(80, 140);
 * end
 * @example
 */
int cylinder(lua_State *L);

/**
 * Draw a 3D Torus. 
 *
 * @visual
 *
 * @param [radius] radius of the torus. Defaults to 50.
 * @param [tubeRadius] radius of the tube. Defaults to 10.
 * @param [detailX] number of edges that form the hole. Defaults to 24.
 * @param [detailY] number of triangle subdivisions along the y-axis. Defaults to 16.
 *
 * @example
 * function setup()
 *   createWindow(300, 300, GL3D);
 * end
 *
 * function draw()
 *   background('purple');
 *  
 *   torus(180, 80);
 * end
 * @example
 */
int torus(lua_State *L);


#endif /* _LU5_SHAPES3D_H_ */