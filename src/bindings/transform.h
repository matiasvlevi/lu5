#ifndef _LU5_TRANSFORM_H_
#define _LU5_TRANSFORM_H_

#include <lua.h>

/**
 * Rotate geometry around the X axis.
 * 
 * @param angle The angle of rotation
 */
int rotateX(lua_State *L);

/**
 * Rotate geometry around the Y axis.
 * 
 * @param angle The angle of rotation
 */
int rotateY(lua_State *L);

/**
 * Rotate geometry around the Z axis.
 * 
 * @param angle The angle of rotation
 */
int rotateZ(lua_State *L);

/**
 * Rotate geometry in 2D.
 * 
 * @param angle The angle of rotation
 */
int rotate(lua_State *L);

/**
 * scale geometry.
 * 
 * @param x The x scaling
 * @param y The y scaling
 * @param [z] The z scaling
 */
int scale(lua_State *L);

/**
 * translate geometry.
 * 
 * @param x The x translation
 * @param y The y translation
 * @param [z] The z translation
 *
 */
int translate(lua_State *L);

#endif /* _LU5_TRANSFORM_H_ */