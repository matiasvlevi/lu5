#include "typography.h"

#include <lauxlib.h>

#include "../lu5_font.h"
#include "../lu5_list.h"
#include "../lu5_types.h"

#include "../lu5_window.h"

#include "../geometry/lu5_geometry.h"

int loadFont(lua_State *L) 
{	
	const char *font_path = lu5_assert_string(L, 1, "loadFont");
	if (!font_path) {
		// If default font is defined
		if (lu5.font_default != NULL) {
			LU5_WARN_TRACE(L, "Returning default font, Expected first argument to be a string");
			
			// return default font
			lua_pushinteger(L, 0);
			return 1;
		} else {

			// Throw
			luaL_error(L, "Expected first argument to be a string");
			return 0;
		}
	}

	lu5_font *current_font;
	int err = lu5_load_font(&lu5, &current_font, font_path);
	
	// On success
	if (err == FT_Err_Ok) {
		// Return the fontId

		// Add the font reference to the list
		lu5_list_push(&(lu5.fonts), current_font, sizeof(lu5_font)); 

		// Return the reference
		lua_pushlightuserdata(L, current_font);
		return 1;
	}

	// Throw
	switch(err) {
		case FT_Err_Ok: break;
		case FT_Err_Cannot_Open_Resource: {
			// If default font is defined
			if (lu5.font_default != NULL) {
				LU5_WARN_TRACE(L, "Could not find font '%s', returning default font", font_path);
				break;
			} else {

				// Throw
				luaL_error(L, "Could not find font '%s'", font_path);
				return 0;
			}
			break;
		}
		case FT_Err_Unknown_File_Format: {
			luaL_error(L, "Unknown file format for font '%s'", font_path);
			return 0;
		}
		case FT_Err_Out_Of_Memory: {
			luaL_error(L, "No memory left to load font '%s'", font_path);
			return 0;
		}

		default: {		
			luaL_error(L, "Could not find font '%s'", font_path);
			return 0;
		}
	}

	// Return default font
	lua_pushlightuserdata(L, lu5.font_default);
	return 1;
}

int textSize(lua_State *L)
{
	lua_Number size = lu5_assert_number(L, 1, "textSize");

	// Get font, if none available, use default.
	lu5_font *font = lu5.style.font_current;
	if (font == NULL) {
		font = lu5.font_default;
	}

	if (font == NULL) {
		// TODO: avoid having this warning
		LU5_WARN("textSize needs to be called after creating the window");
		return 0;
	}

	FT_Set_Char_Size(
		font->face,
		0,
		size * 64,
		0,
		0
	);

	lu5.style.fontSize = size;

	return 0;
}

int textAlign(lua_State *L)
{
	lua_Integer mode = lu5_assert_integer(L, 1, "textAlign");

	if (mode <= LU5_TEXTALIGN_MODE_COUNT)
	{
		lu5_style(&lu5)->textAlign = mode;
	}

	return 0;
}

int textFont(lua_State *L)
{
	// Check if valid
	if (!lua_islightuserdata(L, 1)) {
		luaL_error(L, "Expected first argument to be a font ptr");
	
		return 0;
	}

	// Get the font ptr
	lu5_font *font_id = (lu5_font *)lua_touserdata(L, 1);
	
	// Set the current font ptr
	lu5.style.font_current = font_id;

	return 0;
}

int text(lua_State *L)
{
	const char *str = lu5_assert_string(L, 1, "text");

	lua_Number x = lua_tonumber(L, 2);
	lua_Number y = lua_tonumber(L, 3);

	lu5_apply_color(lu5.style.fill);
	 
	// Get font, if none available, use default.
	lu5_font *font = lu5.style.font_current;
	if (font == NULL) {
		font = lu5.font_default;
	}

	if (font == NULL) {
		LU5_WARN("text needs to be called after creating the window");
		return 0;
	}

	lu5_2D_over_3D_begin(lu5.depth_mode, lu5.width, lu5.height);

    lu5_apply_color(lu5.style.fill);
	lu5_render_text(str, x, y, lu5.style.fontSize, font);

	lu5_2D_over_3D_end(lu5.depth_mode);

	return 0;
}
