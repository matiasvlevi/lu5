#include "lu5_bindings.h"

#include "bindings/classes.h"
#include "bindings/window.h"
#include "bindings/setting.h"
#include "bindings/lu5_math.h"
#include "bindings/io.h"
#include "bindings/shapes.h"
#include "bindings/mouse.h"
#include "bindings/keyboard.h"
#include "bindings/typography.h"
#include "bindings/image.h"

void lu5_update_dynamic_variables(lu5_State *l5, GLFWwindow *window) 
{
	
	double mouseX, mouseY;
	glfwGetCursorPos(window, &mouseX, &mouseY);
	LUA_ADD_NUMBER_GLOBAL_BY_NAME(l5->L, LU5_MOUSE_X, mouseX);
	LUA_ADD_NUMBER_GLOBAL_BY_NAME(l5->L, LU5_MOUSE_Y, mouseY);

	int mouseIsPressed = glfwGetMouseButton(window, 0);
	LUA_ADD_BOOL_GLOBAL_BY_NAME(l5->L, LU5_MOUSE_IS_PRESSED, mouseIsPressed);

	if (l5->env.target_framerate == -1) {
		// For free frame rates
		LUA_ADD_NUMBER_GLOBAL_BY_NAME(l5->L, LU5_DELTA_TIME, l5->env.delta_time);
	} else {
		// For fixed frame rates
		LUA_ADD_NUMBER_GLOBAL_BY_NAME(l5->L, LU5_DELTA_TIME, (lu5.env.now_time - lu5.env.last_frame_time));
	}
}


static void lu5_register_constants(lua_State *L) 
{
	LUA_ADD_NUMBER_GLOBAL_BY_NAME(L, "LEFT_ARROW" , LU5_KEY_LEFT_ARROW);
	LUA_ADD_NUMBER_GLOBAL_BY_NAME(L, "RIGHT_ARROW", LU5_KEY_RIGHT_ARROW);
	LUA_ADD_NUMBER_GLOBAL_BY_NAME(L, "UP_ARROW"   , LU5_KEY_UP_ARROW);
	LUA_ADD_NUMBER_GLOBAL_BY_NAME(L, "DOWN_ARROW" , LU5_KEY_DOWN_ARROW);

	LUA_ADD_NUMBER_GLOBAL_BY_NAME(L, "ENTER"      , LU5_KEY_ENTER);
	LUA_ADD_NUMBER_GLOBAL_BY_NAME(L, "BACKSPACE"  , LU5_KEY_BACKSPACE);

	// NUMBER KEYS (0-9)
	LUA_ADD_NUMBER_GLOBAL_BY_NAME(L, "KEY_0" , GLFW_KEY_0);
	LUA_ADD_NUMBER_GLOBAL_BY_NAME(L, "KEY_1" , GLFW_KEY_1);
	LUA_ADD_NUMBER_GLOBAL_BY_NAME(L, "KEY_2" , GLFW_KEY_2);
	LUA_ADD_NUMBER_GLOBAL_BY_NAME(L, "KEY_3" , GLFW_KEY_3);
	LUA_ADD_NUMBER_GLOBAL_BY_NAME(L, "KEY_4" , GLFW_KEY_4);
	LUA_ADD_NUMBER_GLOBAL_BY_NAME(L, "KEY_5" , GLFW_KEY_5);
	LUA_ADD_NUMBER_GLOBAL_BY_NAME(L, "KEY_6" , GLFW_KEY_6);
	LUA_ADD_NUMBER_GLOBAL_BY_NAME(L, "KEY_7" , GLFW_KEY_7);
	LUA_ADD_NUMBER_GLOBAL_BY_NAME(L, "KEY_8" , GLFW_KEY_8);
	LUA_ADD_NUMBER_GLOBAL_BY_NAME(L, "KEY_9" , GLFW_KEY_9);

	// Alphabet Keys
	LUA_ADD_NUMBER_GLOBAL_BY_NAME(L, "KEY_A" , GLFW_KEY_A);
	LUA_ADD_NUMBER_GLOBAL_BY_NAME(L, "KEY_B" , GLFW_KEY_B);
	LUA_ADD_NUMBER_GLOBAL_BY_NAME(L, "KEY_C" , GLFW_KEY_C);
	LUA_ADD_NUMBER_GLOBAL_BY_NAME(L, "KEY_D" , GLFW_KEY_D);
	LUA_ADD_NUMBER_GLOBAL_BY_NAME(L, "KEY_E" , GLFW_KEY_E);
	LUA_ADD_NUMBER_GLOBAL_BY_NAME(L, "KEY_F" , GLFW_KEY_F);
	LUA_ADD_NUMBER_GLOBAL_BY_NAME(L, "KEY_G" , GLFW_KEY_G);
	LUA_ADD_NUMBER_GLOBAL_BY_NAME(L, "KEY_H" , GLFW_KEY_H);
	LUA_ADD_NUMBER_GLOBAL_BY_NAME(L, "KEY_I" , GLFW_KEY_I);
	LUA_ADD_NUMBER_GLOBAL_BY_NAME(L, "KEY_J" , GLFW_KEY_J);
	LUA_ADD_NUMBER_GLOBAL_BY_NAME(L, "KEY_K" , GLFW_KEY_K);
	LUA_ADD_NUMBER_GLOBAL_BY_NAME(L, "KEY_L" , GLFW_KEY_L);
	LUA_ADD_NUMBER_GLOBAL_BY_NAME(L, "KEY_M" , GLFW_KEY_M);
	LUA_ADD_NUMBER_GLOBAL_BY_NAME(L, "KEY_N" , GLFW_KEY_N);
	LUA_ADD_NUMBER_GLOBAL_BY_NAME(L, "KEY_O" , GLFW_KEY_O);
	LUA_ADD_NUMBER_GLOBAL_BY_NAME(L, "KEY_P" , GLFW_KEY_P);
	LUA_ADD_NUMBER_GLOBAL_BY_NAME(L, "KEY_Q" , GLFW_KEY_Q);
	LUA_ADD_NUMBER_GLOBAL_BY_NAME(L, "KEY_R" , GLFW_KEY_R);
	LUA_ADD_NUMBER_GLOBAL_BY_NAME(L, "KEY_S" , GLFW_KEY_S);
	LUA_ADD_NUMBER_GLOBAL_BY_NAME(L, "KEY_T" , GLFW_KEY_T);
	LUA_ADD_NUMBER_GLOBAL_BY_NAME(L, "KEY_U" , GLFW_KEY_U);
	LUA_ADD_NUMBER_GLOBAL_BY_NAME(L, "KEY_V" , GLFW_KEY_V);
	LUA_ADD_NUMBER_GLOBAL_BY_NAME(L, "KEY_W" , GLFW_KEY_W);
	LUA_ADD_NUMBER_GLOBAL_BY_NAME(L, "KEY_X" , GLFW_KEY_X);
	LUA_ADD_NUMBER_GLOBAL_BY_NAME(L, "KEY_Y" , GLFW_KEY_Y);
	LUA_ADD_NUMBER_GLOBAL_BY_NAME(L, "KEY_Z" , GLFW_KEY_Z);

	// Other common keys
	LUA_ADD_NUMBER_GLOBAL_BY_NAME(L, "KEY_BACKSLASH", GLFW_KEY_BACKSLASH);
	LUA_ADD_NUMBER_GLOBAL_BY_NAME(L, "KEY_GRAVE_ACCENT" , GLFW_KEY_GRAVE_ACCENT);
	LUA_ADD_NUMBER_GLOBAL_BY_NAME(L, "KEY_ESCAPE" , GLFW_KEY_ESCAPE);
	LUA_ADD_NUMBER_GLOBAL_BY_NAME(L, "KEY_TAB" , GLFW_KEY_TAB);
	LUA_ADD_NUMBER_GLOBAL_BY_NAME(L, "KEY_INSERT" , GLFW_KEY_INSERT);
	LUA_ADD_NUMBER_GLOBAL_BY_NAME(L, "KEY_DELETE", GLFW_KEY_DELETE);
	LUA_ADD_NUMBER_GLOBAL_BY_NAME(L, "KEY_PAGE_UP" , GLFW_KEY_PAGE_UP);
	LUA_ADD_NUMBER_GLOBAL_BY_NAME(L, "KEY_PAGE_DOWN", GLFW_KEY_PAGE_DOWN);
	LUA_ADD_NUMBER_GLOBAL_BY_NAME(L, "KEY_HOME", GLFW_KEY_HOME);
	LUA_ADD_NUMBER_GLOBAL_BY_NAME(L, "KEY_END", GLFW_KEY_END);
	LUA_ADD_NUMBER_GLOBAL_BY_NAME(L, "KEY_CAPS_LOCK", GLFW_KEY_CAPS_LOCK);

	// GL Primitives
	LUA_ADD_INTEGER_GLOBAL_BY_NAME(L, "POINTS"        , GL_POINTS);
	LUA_ADD_INTEGER_GLOBAL_BY_NAME(L, "QUADS"         , GL_QUADS);
	LUA_ADD_INTEGER_GLOBAL_BY_NAME(L, "LINES"         , GL_LINES);
	LUA_ADD_INTEGER_GLOBAL_BY_NAME(L, "LINE_STRIP"    , GL_LINE_STRIP);
	LUA_ADD_INTEGER_GLOBAL_BY_NAME(L, "LINE_LOOP"     , GL_LINE_LOOP);
	LUA_ADD_INTEGER_GLOBAL_BY_NAME(L, "TRIANGLES"     , GL_TRIANGLES);
	LUA_ADD_INTEGER_GLOBAL_BY_NAME(L, "TRIANGLE_STRIP", GL_TRIANGLE_STRIP);
	LUA_ADD_INTEGER_GLOBAL_BY_NAME(L, "TRIANGLE_FAN"  , GL_TRIANGLE_FAN);
	LUA_ADD_INTEGER_GLOBAL_BY_NAME(L, "QUAD_STRIP"    , GL_QUAD_STRIP);

	// Math constants
	LUA_ADD_NUMBER_GLOBAL_BY_NAME(L, "TWO_PI"    , LU5_TWO_PI);
	LUA_ADD_NUMBER_GLOBAL_BY_NAME(L, "PI"        , LU5_PI);
	LUA_ADD_NUMBER_GLOBAL_BY_NAME(L, "HALF_PI"   , LU5_HALF_PI);
	LUA_ADD_NUMBER_GLOBAL_BY_NAME(L, "QUARTER_PI", LU5_QUARTER_PI);
}

void lu5_register_symbols(lua_State *L) 
{
	LUA_ADD_STRING_GLOBAL_BY_NAME(L, "VERSION", LU5_VERSION);

	// IO
	LUA_ADD_FUNCTION(L, print);
	LUA_ADD_FUNCTION(L, loadStrings);
	LUA_ADD_FUNCTION(L, loadText);

	// Window
	LUA_ADD_FUNCTION(L, createWindow);
	LUA_ADD_FUNCTION(L, background);
	LUA_ADD_FUNCTION(L, frameRate);

	// Input
	LUA_ADD_FUNCTION(L, keyIsDown);

	// Setting
	LUA_ADD_FUNCTION(L, push);
	LUA_ADD_FUNCTION(L, pop);
	LUA_ADD_FUNCTION(L, fill);
	LUA_ADD_FUNCTION(L, noFill);	
	LUA_ADD_FUNCTION(L, stroke);
	LUA_ADD_FUNCTION(L, noStroke);
	LUA_ADD_FUNCTION(L, strokeWeight);    

	LUA_ADD_FUNCTION(L, beginShape);
	LUA_ADD_FUNCTION(L, vertex);
	LUA_ADD_FUNCTION(L, endShape);

	// Shapes
	LUA_ADD_FUNCTION(L, circle);
	LUA_ADD_FUNCTION(L, ellipse);
	LUA_ADD_FUNCTION(L, square); 
	LUA_ADD_FUNCTION(L, rect); 
	LUA_ADD_FUNCTION(L, quad);
	LUA_ADD_FUNCTION(L, line);
	LUA_ADD_FUNCTION(L, triangle);
	LUA_ADD_FUNCTION(L, point);
	LUA_ADD_FUNCTION(L, arc);

	// Typography
	LUA_ADD_FUNCTION(L, loadFont);
	LUA_ADD_FUNCTION(L, text);
	LUA_ADD_FUNCTION(L, textSize);
	LUA_ADD_FUNCTION(L, textFont);

	// Images
	LUA_ADD_FUNCTION(L, image);
	LUA_ADD_FUNCTION(L, loadImage);

	// OOP
	LUA_ADD_FUNCTION_BY_NAME(L, "class", lu5_class);

	// Vector
	lu5_bind_vector(L);

	// MATH
	LUA_ADD_FUNCTION_BY_NAME(L,"randomSeed", lu5_randomSeed);
	LUA_ADD_FUNCTION_BY_NAME(L,    "random", lu5_random);
	LUA_ADD_FUNCTION_BY_NAME(L,     "round", lu5_round);
	LUA_ADD_FUNCTION_BY_NAME(L,      "ceil", lu5_ceil);
	LUA_ADD_FUNCTION_BY_NAME(L,     "floor", lu5_floor);
	LUA_ADD_FUNCTION_BY_NAME(L,       "sin", lu5_sin);
	LUA_ADD_FUNCTION_BY_NAME(L,       "cos", lu5_cos);
	LUA_ADD_FUNCTION_BY_NAME(L,       "tan", lu5_tan);
	LUA_ADD_FUNCTION_BY_NAME(L,       "max", lu5_max);
	LUA_ADD_FUNCTION_BY_NAME(L,       "min", lu5_min);
	LUA_ADD_FUNCTION_BY_NAME(L,       "abs", lu5_abs);
	LUA_ADD_FUNCTION_BY_NAME(L,       "map", lu5_map);
	LUA_ADD_FUNCTION_BY_NAME(L,      "dist", lu5_dist);
	LUA_ADD_FUNCTION_BY_NAME(L, "constrain", lu5_constrain);


	lu5_register_constants(L);
}

void lu5_register_number_array(lua_State *L, const char* array_name, double *list, size_t size)
{
	lua_newtable(L);

	for (int i = 0; i < size; i++) {
		lua_pushnumber(L, i+1);
		lua_pushnumber(L, list[i]);
		lua_settable(L, -3);
	}

	lua_setglobal(L, array_name);  
}

void lu5_register_integer_array(lua_State *L, const char* array_name, int *list, size_t size)
{
	lua_newtable(L);

	for (int i = 0; i < size; i++) {
		lua_pushnumber(L, i+1);
		lua_pushinteger(L, list[i]);
		lua_settable(L, -3);
	}

	lua_setglobal(L, array_name);  
}

void lu5_register_string_array(lua_State *L, const char* array_name, const char **list, size_t size)
{
	lua_newtable(L);

	for (int i = 0; i < size; i++) {
		lua_pushnumber(L, i+1);
		lua_pushstring(L, list[i]);
		lua_settable(L, -3);
	}

	lua_setglobal(L, array_name);  
}
