#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "bindings.h"

#include "readFile.h"
#include "colorArgs.h"
#include "defs.h"
#include "window.h"

#include <stdbool.h>

#include "print.h"

#include <math.h>
#define PI 3.14159265358979323846

#define GET_COLOR_FROM_LUA_ARGS(l)\
    double r = lua_tonumber(L, 1);\
    double g = r;\
    if(lua_gettop(l) > 1) g = lua_tonumber(L, 2);\
    double b = r;\
    if(lua_gettop(l) > 2) b = lua_tonumber(L, 3);\
    double a = 0xFF; \
    if(lua_gettop(l) > 3) a = lua_tonumber(L, 4)
    

#define WINDOW_TITLE_MAX_SIZE 256
// Forward declaration for size change callback
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

//
int createWindow(lua_State *L) {
    
    int screenWidth = lua_tointeger(L, 1);
    int screenHeight = lua_tointeger(L, 2);
    LUA_ADD_NUMBER_GLOBAL(L, "width", screenWidth);
    LUA_ADD_NUMBER_GLOBAL(L, "height", screenHeight); 

    char window_title[WINDOW_TITLE_MAX_SIZE];

    lua_getglobal(L, "sketch");
    const char *sketch_path = luaL_checkstring(L, -1);
    if (sketch_path == NULL) return 1;
    sprintf(window_title, "[lu5]: %s", sketch_path);

    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(
        screenWidth, screenHeight,     
        window_title, 
        NULL, NULL);

    if (window == NULL)
    {
        glfwTerminate();
        fprintf(stderr, "Failed to create GLFW window\n");
        return 0;
    }

    lua_pushlightuserdata(L, window);
    lua_setglobal(L, "window");

    // Make the window's context current
    glfwMakeContextCurrent(window);

    // Set callback for when the window is resized
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Configure for 2D
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0f, screenWidth, screenHeight, 0.0f, -1.0f, 1.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    return 0;
}

int background(lua_State *L) {
    GET_COLOR_FROM_LUA_ARGS(L);

    glClearColor(r/255, g/255, b/255, a/255);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    return 0;
}


int circle(lua_State *L) {
    double x = lua_tonumber(L, 1);  
    double y = lua_tonumber(L, 2);  
    double d = lua_tonumber(L, 3);  

    float radius = d / 2.0f;
    float angleStep = 2 * PI / LU5_CIRCLE_SEGMENTS;

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y); // Center of the circle
    
    for (int i = 0; i <= LU5_CIRCLE_SEGMENTS; i++) {
        float angle = angleStep * i;
        float x_offset = radius * cos(angle);
        float y_offset = radius * sin(angle);

        glVertex2f(x + x_offset, y + y_offset);
    }

    glEnd();

    return 0;
}

int rect(lua_State *L) {
    double x = lua_tonumber(L, 1);  
    double y = lua_tonumber(L, 2);  
    double w = lua_tonumber(L, 3);  

    double h = w;
    if (lua_gettop(L) > 3) {
        h = lua_tonumber(L, 4);
    }  

    float x2 = x + w;
    float y2 = y + h;

    glBegin(GL_QUADS);
        glVertex2f(x, y);
        glVertex2f(x2, y);
        glVertex2f(x2, y2);
        glVertex2f(x, y2);
    glEnd(); 

    return 0;
}

int line(lua_State *L) 
{
    double x1 = lua_tonumber(L, 1);
    double y1 = lua_tonumber(L, 2);
    double x2 = lua_tonumber(L, 3);
    double y2 = lua_tonumber(L, 4);

    int segments = 20;  // More segments = rounder circle
    float angleStep = (2 * PI) / segments;
    float radius = (float)lu5.style.strokeWeight / 2.0f;

    glLineWidth(lu5.style.strokeWeight * 5);

    glBegin(GL_QUADS);
        glVertex2f(x1+radius, y1-radius);
        glVertex2f(x1-radius, y1+radius);
        
        glVertex2f(x2+radius, y2-radius);
        glVertex2f(x2-radius, y2+radius);
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x1, y1);
    for (int i = 0; i <= segments; i++) {
        float angle = i * angleStep;
        float x = x1 + cos(angle) * radius;
        float y = y1 + sin(angle) * radius;
        glVertex2f(x, y);
    }
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x2, y2);
    for (int i = 0; i <= segments; i++) {
        float angle = i * angleStep;
        float x = x2 + cos(angle) * radius;
        float y = y2 + sin(angle) * radius;
        glVertex2f(x, y);
    }
    glEnd();


    return 0;
}

int text(lua_State *L)
{
    const char *str = luaL_checkstring(L, 1);
    if (!str) {
        luaL_error(L, "Expected a string argument");
        return 0;
    }

    double x = lua_tonumber(L, 2);
    double y = lua_tonumber(L, 3);

    printf("TODO: Implement text.\t text(\"%s\", %i, %i);", str, x, y);
    return 0;
}

int strokeWeight(lua_State *L) 
{
    double weight = lua_tonumber(L, 1);

    glLineWidth(weight);

    lu5.style.strokeWeight = weight;

    return 0;
}

int fill(lua_State *L) 
{
    GET_COLOR_FROM_LUA_ARGS(L);

    glColor4ub(r, g, b, a);

    return 0;
}

int isKeyDown(lua_State *L) 
{
    int key = lua_tointeger(L, 1);

    bool down = false;

    if ((key > 0) && (key < MAX_KEYBOARD_KEYS))
    {
        down = (lu5.input.keyboard.current_keys[key] == 1);
    }

    lua_pushboolean(L, down);
    return 1;
}

int print(lua_State *L)
{
    int argc = lua_gettop(L);

    // Print all arguments
    for (int i = 0; i < argc-1; i++) {
        print_any(L, i+1, 0, ' ');
    }
    print_any(L, argc, 0, '\n');

    return 0;
}

void lu5_update_dynamic_variables(lua_State *L, GLFWwindow *window) { 
    double mouseX, mouseY;
    glfwGetCursorPos(window, &mouseX, &mouseY);

    int mouseIsPressed = glfwGetMouseButton(window, 0);

    LUA_ADD_CONST_NUMBER_GLOBAL(L, mouseX);
    LUA_ADD_CONST_NUMBER_GLOBAL(L, mouseY);

    LUA_ADD_CONST_BOOL_GLOBAL(L, mouseIsPressed);
}

void lu5_register_symbols(lua_State *L) 
{

    LUA_ADD_FUNCTION(L, print);
    LUA_ADD_FUNCTION(L, createWindow);
    LUA_ADD_FUNCTION(L, background);
    LUA_ADD_FUNCTION(L, fill);
    LUA_ADD_FUNCTION(L, strokeWeight);
    LUA_ADD_FUNCTION(L, text);

    LUA_ADD_FUNCTION(L, circle);
    LUA_ADD_FUNCTION(L, rect); 
    LUA_ADD_FUNCTION(L, line);
    LUA_ADD_FUNCTION(L, isKeyDown);

    LUA_ADD_NUMBER_GLOBAL(L, "LEFT_ARROW",  263);
    LUA_ADD_NUMBER_GLOBAL(L, "RIGHT_ARROW", 262);
    LUA_ADD_NUMBER_GLOBAL(L, "UP_ARROW",    265);
    LUA_ADD_NUMBER_GLOBAL(L, "DOWN_ARROW",  264);
    LUA_ADD_NUMBER_GLOBAL(L, "ENTER",       257);
    LUA_ADD_NUMBER_GLOBAL(L, "BACKSPACE",   259);
}

// Callback function for when the window's size is changed
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
