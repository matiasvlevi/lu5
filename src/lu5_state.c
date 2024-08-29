#include "lu5_state.h"

#include "lu5_window.h"

lu5_State lu5 = {
	// use LU5_ERROR_LOG for no logging
	.log_level = LU5_WARN_LOG,
	.window = NULL,
	.width = 0.0f,
	.height = 0.0f,
	.depth_mode = LU5_GL2D,
	.style = {
		.fontSize = 22,
		.fill = LU5_WHITE,
		.stroke = LU5_BLACK,
		.strokeWeight = 2,
		.font_current = NULL
	},
	.style_cache = {
		.fontSize = 22,
		.fill = LU5_WHITE,
		.stroke = LU5_BLACK,
		.strokeWeight = 2,
		.font_current = NULL
	},
	.input = {
		.mouse = {
			.actions = {},
			.pmouseX = 0.0f,
			.pmouseY = 0.0f,
			.scrollY = 0.0f
		}
	},
	.env = {
		// Set no limit
		.target_framerate = -1,
		.restart = false
	},
	.orbit = NULL
};
