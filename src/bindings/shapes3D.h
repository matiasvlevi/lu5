#ifndef _LU5_SHAPES3D_H_
#define _LU5_SHAPES3D_H_
/**
 * @module 3D Shapes
 */
#include <lua.h>

/**
 * Draw a plane 
 * 
 * @param w The width dimension 
 * @param h The height dimension
 *
 */
int plane(lua_State *L);

/**
 * Draw a 3D box 
 * 
 * @param w The width dimension 
 * @param [h] The height dimension
 * @param [d] The depth dimension
 *
 */
int box(lua_State *L);

/**
 * Draw a 3D Sphere 
 * 
 * @param w The width dimension 
 * @param [detailX] The detail in the X axis
 * @param [detailY] the detailt in the Y axis
 *
 */
int sphere(lua_State *L);


#endif /* _LU5_SHAPES3D_H_ */