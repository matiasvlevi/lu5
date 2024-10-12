#include "lu5_state.h"

#include "lu5_window.h"
#include "bindings/setting.h"
#include "bindings/typography.h"


#include <stdlib.h>

lu5_State lu5 = {
	// use LU5_ERROR_LOG for no logging
	.log_level = LU5_WARN_LOG,
	.debug = false,
	.window = NULL,
	.width = 0.0f,
	.height = 0.0f,
	.depth_mode = LU5_GL2D,
	.loop = true,

	.style_stack = {},
	.style_stack_len = 0,

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

void lu5_init_state(lu5_State *l5)
{
	l5->loop = true;

	lu5_style_setting style;
	lu5_set_style(&style);
	lu5_style_push(l5, &style);

	// Non-limited framerate
	l5->env.target_framerate = -1;
	l5->env.restart = false;

	if (l5->orbit != NULL) { 
		free(l5->orbit);
	}
	l5->orbit = NULL;
}