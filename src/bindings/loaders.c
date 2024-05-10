#include "loaders.h"
#include <lauxlib.h>

#include "../lu5_logger.h"
#include "../lu5_font.h"

int loadFont(lua_State *L) {
	
	const char *font_path = lua_tostring(L, 1);

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

int loadImage(lua_State *L) {
	return 0;
}

int loadJSON(lua_State *L) {
	return 0;
}

int loadCSV(lua_State *L) {
	return 0;
}

int loadText(lua_State *L) {
	return 0;
}
