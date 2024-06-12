#include "image.h"
#include <lauxlib.h>

#include "../lu5_image.h"
#include "../lu5_types.h"

int loadImage(lua_State *L) 
{
	const char *image_path = lu5_assert_string(L, 1, "loadImage");
	if (!image_path) {
		// Throw
		luaL_error(L, "Expected first argument to be a string");
		return 0;
	}

	// Returns the loaded image ptr
	lu5_image *img = lu5_load_image(&lu5, image_path);

	lua_pushlightuserdata(L, img);
	return 1;
}

int image(lua_State *L) 
{
	// Get image reference
	if (!lua_islightuserdata(L, 1)) {
		luaL_error(L, "Expected first argument to be an image ptr");
		return 0;
	}

	lu5_image *img = (lu5_image *)lua_touserdata(L, 1);

	// Get position arguments
	double x = lua_tonumber(L, 2);
	double y = lua_tonumber(L, 3);

	// Get optional width argument
	double w = img->width;
	if (lua_isnumber(L, 4)) {
		w = lua_tonumber(L, 4);
	}

	// Get optional height
	double h = img->height;
	if (lua_isnumber(L, 5)) {
		h = lua_tonumber(L, 5);
	}

	LU5_APPLY_COLOR(lu5.style.fill);
	lu5_render_image(L, img->texture, x, y, w, h);

	return 0;
}