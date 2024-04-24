#include "events.h"
#include "window.h"

#include <stdio.h>

static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {

    if (!lu5.L) return;

    lu5.input.mouse.actions[button] = action;
  
    if (action == 1) {
        lua_getglobal(lu5.L, "mousePressed");
    } else {
        lua_getglobal(lu5.L, "mouseReleased");
    }

    if (lua_isfunction(lu5.L, -1)) {
        lua_pushinteger(lu5.L, button);

        if (lua_pcall(lu5.L, 1, 0, 0) != LUA_OK) {
            fprintf(stderr, "[\x1b[91mERROR\x1b[0m]: %s\n", lua_tostring(lu5.L, -1));
        }
    }
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (!lu5.L) return;

    // TODO: Force down state when CAPS lock or other mods found

    // Check if there is space available in the key queue
    if ((lu5.input.keyboard.keypress_queue_count < MAX_KEY_PRESSED_QUEUE) && (action == GLFW_PRESS))
    {
        // Add key to queue
        lu5.input.keyboard.keypress_queue[lu5.input.keyboard.keypress_queue_count] = key;
        lu5.input.keyboard.keypress_queue_count++;
    }

    switch(action) {
        case GLFW_RELEASE: 
            lu5.input.keyboard.current_keys[key] = GLFW_RELEASE;

            // Get keyReleased
            lua_getglobal(lu5.L, "keyReleased");
            break;
        case GLFW_PRESS: 
            lu5.input.keyboard.current_keys[key] = GLFW_PRESS;

            // Get keyPressed
            lua_getglobal(lu5.L, "keyPressed");
            break;
        case GLFW_REPEAT:
            lu5.input.keyboard.current_keys[key] = GLFW_REPEAT;
            
            // Get keyHeld
            lua_getglobal(lu5.L, "keyHeld");
            break;
    }

    // Check if callback event is a function
    if (lua_isfunction(lu5.L, -1)) {
        lua_pushinteger(lu5.L, key);

        if (lua_pcall(lu5.L, 1, 0, 0) != LUA_OK) {
            fprintf(stderr, "[\x1b[91mERROR\x1b[0m]: %s\n", lua_tostring(lu5.L, -1));
        }
    }

}

void lu5_poll_events(GLFWwindow *window) 
{
    glfwPollEvents();             
    glfwSwapBuffers(window);
}

void lu5_register_event_callbacks(GLFWwindow *window) {

    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetKeyCallback(window, key_callback);

    return;
}
    



