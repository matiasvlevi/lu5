#include "lu5_state.h"

#include "lu5_color.h"

lu5_State lu5 = {
	// use LU5_ERROR_LOG for no logging
	.log_level = LU5_WARN_LOG,
	.style = {
		.strokeWeight = 1,
		.stroke = LU5_BLACK,
		.fill = LU5_WHITE,
		.fontSize = 22,
		.fontId = 0
	},
	.env = {
		// Set no limit
		.target_framerate = -1
	},
	.fonts = {},
	.font_count = 0,
};

// Callback function for when the window's size is changed
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
