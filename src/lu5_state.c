#include "lu5_state.h"

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

#include "lu5_bindings.h"
#include "lu5_color.h"
#include "lu5_image.h"
#include "lu5_font.h"

lu5_State lu5 = {
	// use LU5_ERROR_LOG for no logging
	.log_level = LU5_WARN_LOG,
	.style = {
		.fontSize = 22,
		.fill = LU5_WHITE,
		.stroke = LU5_BLACK,
		.strokeWeight = 1,
		.font_current = NULL
	},
	.style_cache = {
		.fontSize = 22,
		.fill = LU5_WHITE,
		.stroke = LU5_BLACK,
		.strokeWeight = 1,
		.font_current = NULL
	}, 
	.env = {
		// Set no limit
		.target_framerate = -1
	}
};

void lu5_init(lu5_State *l5)
{	
	l5->L = luaL_newstate();
	luaL_openlibs(l5->L);

	lu5_init_freetype(l5);

	// Register functions & constants
	lu5_register_symbols(l5->L);
	lu5_register_colors(l5->L);
}

void lu5_close(lu5_State *l5) 
{
	lu5_close_images(l5);

	lu5_close_fonts(l5);

	FT_Done_FreeType(l5->ft);

	lua_close(l5->L);
}
