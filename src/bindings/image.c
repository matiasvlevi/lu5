#include "image.h"
#include <lauxlib.h>

#include "../lu5_image.h"
#include "../lu5_types.h"

#include "../lu5_print.h"

static void lu5_new_image(lua_State *L, lu5_image *img)
{
	// Texture
	lua_newtable(L);
	lua_pushlightuserdata(L, img);
	lua_setfield(L, -2, "texture");

	lua_pushnumber(L, img->width);
	lua_setfield(L, -2, "width");

	lua_pushnumber(L, img->height);
	lua_setfield(L, -2, "height");

	// METATABLE
	lua_newtable(L);
	lua_pushcfunction(L, lu5_image_index);
	lua_setfield(L, -2, "__index");
	lua_pushcfunction(L, lu5_image_get);
	lua_setfield(L, -2, "crop");

	lua_setmetatable(L, -2);
}

int lu5_image_get(lua_State *L) 
{
	lua_getfield(L, 1, "texture");
	if (!lua_islightuserdata(L, -1)) {
		luaL_error(L, "Expected first argument to be an image ptr");
		return 0;
	}

	lu5_image *originalImage = (lu5_image *)lua_touserdata(L, -1);

	int x = lu5_assert_number(L, 2, "Image.get");
	int y = lu5_assert_number(L, 3, "Image.get");
	int w = lu5_assert_number(L, 4, "Image.get");
	int h = lu5_assert_number(L, 5, "Image.get");

	if (
		originalImage->width < x || 
		originalImage->height < y ||
		originalImage->width < w || 
		originalImage->height < h ||
		originalImage->width < (x + w) || 
		originalImage->height < (y + h)
	) {
		luaL_error(L, 
			"Cropping bounds cannot be larger than original image (\x1b[33m%d\x1b[0m x \x1b[33m%d\x1b[0m)", 
			originalImage->width, 
			originalImage->height
		);
		return 0;
	}

	// Add cropped img to images so it gets freed
	lu5_image *croppedImage = lu5_image_crop(&lu5, originalImage, x, y, w, h);

	lu5_new_image(L, croppedImage);

	return 1;
}

int lu5_image_index(lua_State *L) 
{
	lua_getmetatable(L, 1);
	lua_pushvalue(L, 2);
	lua_rawget(L, -2);

	if (lua_isfunction(L, -1)) {
		return 1;
	}
	
	lua_pop(L, 1);
	return 0;
}

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

	lu5_new_image(L, img);

	return 1;
}

int image(lua_State *L) 
{
	lua_getfield(L, 1, "texture");

	// Get image reference
	if (!lua_islightuserdata(L, -1)) {
		luaL_error(L, "Expected first argument to be an image ptr");
		return 0;
	}

	lu5_image *img = (lu5_image *)lua_touserdata(L, -1);

	// Get position arguments
	lua_Number x = lua_tonumber(L, 2);
	lua_Number y = lua_tonumber(L, 3);

	// Get optional width argument
	lua_Number w = img->width;
	if (lua_isnumber(L, 4)) {
		w = lua_tonumber(L, 4);
	}

	// Get optional height
	lua_Number h = img->height;
	if (lua_isnumber(L, 5)) {
		h = lua_tonumber(L, 5);
	}

	lu5_apply_color(lu5.style.fill);
	lu5_render_image(L, img->texture, x, y, w, h);

	return 0;
}

void lu5_image_bind(lua_State *L)
{
	lua_newtable(L);
	lua_pushcfunction(L, lu5_image_get);
	lua_setfield(L, -2, "crop");

	lua_setglobal(L, "Image");
}