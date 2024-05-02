#include "lu5_state.h"

#include "lu5_color.h"

lu5_state lu5 = {
    // use LU5_ERROR_LOG for no logging
    .log_level = LU5_WARN_LOG,
    .style = {
        .strokeWeight = 1,
        .stroke = LU5_BLACK,
        .fill = LU5_WHITE
        
    }
};

// Callback function for when the window's size is changed
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
