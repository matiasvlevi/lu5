#include "lu5_state.h"

lu5_state lu5 = {};

// Callback function for when the window's size is changed
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
