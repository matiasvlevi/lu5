#include "typography.h"

#include <lauxlib.h>

#include "../lu5_list.h"
#include "../lu5_types.h"

#include "../lu5_window.h"

#include "../lu5_geometry.h"
#include "../lu5_font.h"

#include "../lu5_logger.h"

int loadFont(lua_State *L) 
{	
	const char *font_path = lu5_assert_string(L, 1, "loadFont");

	// Return the reference
	lu5_font *font = lu5_load_and_add_font(&lu5, font_path);
	if (font == NULL) {
		// Return default font
		lua_pushlightuserdata(L, lu5.font_default);
	} else {
		lua_pushlightuserdata(L, font);
	}

	return 1;
}

int textSize(lua_State *L)
{
	lua_Number size = lu5_assert_number(L, 1, "textSize");

	#ifndef LU5_WASM
	// Get font, if none available, use default.
	lu5_font *font = lu5_style(&lu5)->font_current;
	if (font == NULL) {
		font = lu5.font_default;
	}

	if (font == NULL) {
		// TODO: avoid having this warning
		LU5_WARN("textSize needs to be called after creating the window");
		return 0;
	}

	// Set font to the current style size
	if (FT_Set_Pixel_Sizes(font->face, 0, size) != FT_Err_Ok) {
		lu5_close_font(font);
		luaL_error(L, "Something went wrong when resizing the font");
		return 0;
	}
	#endif

	lu5_style(&lu5)->fontSize = size;
	
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
	#ifndef LU5_WASM
		if (lua_islightuserdata(L, 1)) {
			// Get the font ptr
			lu5_font *font_id = (lu5_font *)lua_touserdata(L, 1);
			
			// Set the current font ptr
			lu5_style(&lu5)->font_current = font_id;

			return 0;
		}
	#else
		if (lua_isstring(L, 1)) {
			const char *str = lua_tostring(L, 1);
			if (str != NULL) {
				lu5_set_font(str);
				lu5_style(&lu5)->font_current = NULL;
				return 0;
			}
		} else {
			LU5_LOG("In the browser, you should use font names, loadFont is omitted. Use textFont directly. \nex: `textFont('Arial')`");
			return 0;
		}
	#endif

	luaL_error(L, "Expected first argument of textFont to be a font ptr, use \x1b[90mloadFont('/path/to/my/font.ttf')\x1b[0m instead.");

	return 0;

}

int text(lua_State *L)
{
	const char *str = lu5_assert_string(L, 1, "text");

	lua_Number x = lua_tonumber(L, 2);
	lua_Number y = lua_tonumber(L, 3);
	 
	#ifndef LU5_WASM
	// Get font, if none available, use default.
	lu5_font *font = lu5_style(&lu5)->font_current;
	if (font == NULL) {
		font = lu5.font_default;
	}

	if (font == NULL) {
		LU5_WARN("text needs to be called after creating the window");
		return 0;
	}
	#else
	lu5_font *font = NULL;
	#endif

	lu5_2D_over_3D_begin(lu5.depth_mode, lu5.width, lu5.height);

	lu5_render_text(str, x, y, 
		lu5_style(&lu5)->fontSize,
		lu5_style(&lu5)->textAlign, 
		font, 
		lu5_style(&lu5)->fill
	);

	lu5_2D_over_3D_end(lu5.depth_mode);

	return 0;
}
