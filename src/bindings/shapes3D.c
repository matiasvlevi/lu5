
#include "shapes3D.h"
#include <GLFW/glfw3.h>
#include <math.h>

#include "../lu5_types.h"
#include "../lu5_state.h"
#include "../geometry/lu5_geometry.h"

int plane(lua_State *L) 
{
	lua_Number size_x = lu5_assert_number(L, 1, "plane");
	lua_Number size_y = size_x;
	
	if (lua_isnumber(L, 2)) {
		size_y = lua_tonumber(L, 2);
	}

	float half_x = size_x / 2.0f;
	float half_y = size_y / 2.0f;

	if (lu5_has_fill()) 
	{
		lu5_apply_color(lu5_style(&lu5)->fill);
		
		lu5_render_plane_faces(half_x, half_y);
	}

	if (lu5_has_stroke()) 
	{
		lu5_apply_color(lu5_style(&lu5)->stroke);
		glLineWidth(lu5_style(&lu5)->strokeWeight);
		
		lu5_render_plane_edges(half_x, half_y);
	}

	return 0;
}

int box(lua_State *L) 
{
	lua_Number w = lu5_assert_number(L, 1, "box");

	lua_Number h = w;
	if (lua_isnumber(L, 2)) {
		h = lua_tonumber(L, 2);
	}
	
	lua_Number d = h;
	if (lua_isnumber(L, 3)) {
		d = lua_tonumber(L, 3);
	}

	w /= 2.0f;
	h /= 2.0f;
	d /= 2.0f;

	if (lu5_has_fill()) 
	{
		lu5_apply_color(lu5_style(&lu5)->fill);
		
		lu5_render_box_faces(w, h, d);
	}

	if (lu5_has_stroke()) 
	{
		lu5_apply_color(lu5_style(&lu5)->stroke);
		glLineWidth(lu5_style(&lu5)->strokeWeight);

		lu5_render_box_edges(w, h, d);
	}

	return 0;
}

int sphere(lua_State *L) 
{
	lua_Number radius = lu5_assert_number(L, 1, "sphere");

	lua_Number detail_x = 24;
	if (lua_isnumber(L, 2)) {
		detail_x = lua_tonumber(L, 2);
	}
	
	lua_Number detail_y = 16;
	if (lua_isnumber(L, 3)) {
		detail_y = lua_tonumber(L, 3);
	}

	if (lu5_has_fill()) 
	{
		lu5_apply_color(lu5_style(&lu5)->fill);
		lu5_render_ellipsoid_faces(radius, detail_x, detail_y);
	}

	if (lu5_has_stroke()) 
	{
		// Draw sphere edges
		lu5_apply_color(lu5_style(&lu5)->stroke);
		glLineWidth(lu5_style(&lu5)->strokeWeight);

		// Draw stroke with a larger radius
		lu5_render_ellipsoid_edges(
			radius + 1.0f,
			detail_x, detail_y
		);
	}

	return 0;
}

// int cylinder(lua_State *L) 
// {
// 	lua_Number radius = lu5_assert_number(L, 1, "cylinder");
// 	lua_Number height = lu5_assert_number(L, 2, "cylinder");

// 	lua_Number detail_x = 24;
// 	if (lua_isboolean(L, 3)) {
// 		detail_x = lua_toboolean(L, 3);
// 	}
	
// 	lua_Number detail_y = 24;
// 	if (lua_isboolean(L, 4)) {
// 		detail_y = lua_toboolean(L, 4);
// 	}

// 	bool top_cap = false;
// 	if (lua_isboolean(L, 5)) {
// 		top_cap = lua_toboolean(L, 5);
// 	}
	
// 	bool bottom_cap = false;
// 	if (lua_isboolean(L, 6)) {
// 		bottom_cap = lua_toboolean(L, 6);
// 	}

// 	if (lu5_has_fill()) 
// 	{
// 		lu5_apply_color(lu5_style(&lu5)->fill);
// 		lu5_render_cylinder_faces(radius, height,
// 			top_cap, 
// 			bottom_cap);
// 	}

// 	if (lu5_has_stroke()) 
// 	{
// 		// Draw sphere edges
// 		lu5_apply_color(lu5_style(&lu5)->stroke);
// 		glLineWidth(lu5_style(&lu5)->strokeWeight);

// 		// Draw stroke with a larger radius
// 		lu5_render_cylinder_edges(
// 			radius + 1.0f,
// 			height,
// 			detail_x, detail_y
// 			top_cap, 
// 			bottom_cap
// 		);
// 	}

// 	return 0;
// }