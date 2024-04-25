#include "lu5_state.h"

lu5_state lu5 = {
    // use LU5_ERROR_LOG for no logging
    .log_level = LU5_WARN_LOG
};

// Callback function for when the window's size is changed
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
