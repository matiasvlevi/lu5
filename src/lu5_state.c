#include "lu5_state.h"

lu5_State lu5 = {
	// use LU5_ERROR_LOG for no logging
	.log_level = LU5_WARN_LOG,
	.window = NULL,
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
		.target_framerate = -1,
		.restart = false
	}
};
