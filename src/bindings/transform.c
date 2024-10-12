
#include "transform.h"

#include "../lu5_geometry.h"

#include <math.h>

#include "../lu5_types.h"

int translate(lua_State *L) 
{
	lua_Number x = lu5_assert_number(L, 1, "translate");
	lua_Number y = lu5_assert_number(L, 2, "translate");
	lua_Number z = 0;
	if (lua_isnumber(L, 3)) {
		z = lua_tonumber(L, 3);
	}

	lu5_glTranslate(x, y, z);

	return 0;
}

int scale(lua_State *L) 
{
	lua_Number x = lu5_assert_number(L, 1, "scale");
	
	lua_Number y = x;
	if (lua_isnumber(L, 2)) {
		y = lua_tonumber(L, 2);
	}
	
	lua_Number z = y;
	if (lua_isnumber(L, 3)) {
		z = lua_tonumber(L, 3);
	}

	lu5_glScale(x, y, z);

	return 0;
}

int rotate(lua_State *L) 
{
	lua_Number angle = lu5_assert_number(L, 1, "rotate");
	lu5_glTranslate(0.5, 0.5, 0.5);
	lu5_glRotate(angle, 0, 0, 1);
	lu5_glTranslate(-0.5 ,-0.5,-0.5);
	return 0;
}

int rotateX(lua_State *L) 
{
	lua_Number angle = lu5_assert_number(L, 1, "rotateX");

	lu5_glRotate(angle, 1.0f, 0.0f, 0.0f);

	return 0;
}

int rotateY(lua_State *L) 
{
	lua_Number angle = lu5_assert_number(L, 1, "rotateY");

	lu5_glRotate(angle, 0.0f, 1.0f, 0.0f);

	return 0;
}

int rotateZ(lua_State *L) 
{
	lua_Number angle = lu5_assert_number(L, 1, "rotateZ");

	lu5_glRotate(angle, 0.0f, 0.0f, 1.0f);

	return 0;
}