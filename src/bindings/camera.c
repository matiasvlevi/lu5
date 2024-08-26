#include "camera.h"

#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>

#include "../lu5_state.h"
#include "../lu5_logger.h"

#define MOUSE_SENSIBILITY 0.3f
#define ZOOM_SENSIBILITY 0.18f

int orbitControl(lua_State *L) 
{
    // State
    static bool dragging = false;

    static float radius = 600.0f;

    static float camera_angle_y = 0.0f;
    static float camera_angle_x = 0.0f;

    static float angular_velocity_y = 0.0f;
    static float angular_velocity_x = 0.0f;

    static double previousMouseX = 0.0f;
    static double previousMouseY = 0.0f;

    double mouseX, mouseY;
    glfwGetCursorPos(lu5.window, &mouseX, &mouseY);

    // Drag mechanics
    if (lu5.input.mouse.actions[0] == GLFW_PRESS) {
        if (!dragging) {
            dragging = true;
            previousMouseX = mouseX;
            previousMouseY = mouseY;
        } else {
            lua_Number deltaX = previousMouseX - mouseX;
            lua_Number deltaY = mouseY - previousMouseY;
            previousMouseX = mouseX;
            previousMouseY = mouseY;

            angular_velocity_y = deltaX * MOUSE_SENSIBILITY;
            angular_velocity_x = deltaY * MOUSE_SENSIBILITY;
        }
    } else if (lu5.input.mouse.actions[0] == GLFW_RELEASE) {
        dragging = false;
    }

    // Friction when not dragging
    if (!dragging) {
        angular_velocity_y *= 0.94f;
        angular_velocity_x *= 0.94f;
    }

    // apply velocity
    camera_angle_y += angular_velocity_y;
    camera_angle_x -= angular_velocity_x;

    radius += lu5.input.mouse.scrollY * ZOOM_SENSIBILITY;
    lu5.input.mouse.scrollY *= 0.95f;

    // Clamp radius
    radius = fmaxf(0.03f, radius);

    // Clamp pitch
    camera_angle_x = fminf( 89.0f, camera_angle_x);
    camera_angle_x = fmaxf(-89.0f, camera_angle_x);

    float x = radius * cosf(camera_angle_x * M_PI / 180.0f) * sinf(camera_angle_y * M_PI / 180.0f);
    float y = radius * sinf(camera_angle_x * M_PI / 180.0f);
    float z = radius * cosf(camera_angle_x * M_PI / 180.0f) * cosf(camera_angle_y * M_PI / 180.0f);

    glLoadIdentity();
    glScalef(-1, 1, 1);
    gluLookAt(x, y, z, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);


    return 0;
}