
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

int cylinder(lua_State *L)
{
	lua_Number radius = lua_isnumber(L, 1) ? lua_tonumber(L, 1) : 50.0; 
	lua_Number height = lua_isnumber(L, 2) ? lua_tonumber(L, 2) : radius; 

	lua_Number detail_x = lua_isnumber(L, 3) ? lua_tonumber(L, 3) : 24;
	lua_Number detail_y = lua_isnumber(L, 4) ? lua_tonumber(L, 4) : 1;

	bool bottom_cap = lua_isboolean(L, 5) ? lua_toboolean(L, 5) : true;	
	bool top_cap = lua_isboolean(L, 6) ? lua_toboolean(L, 6) : true;

	if (lu5_has_fill()) 
	{
		lu5_apply_color(lu5_style(&lu5)->fill);
		lu5_render_cylinder_faces(radius, height,
			detail_x, detail_y,
			top_cap, 
			bottom_cap);
	}

	if (lu5_has_stroke()) 
	{
		// Draw sphere edges
		lu5_apply_color(lu5_style(&lu5)->stroke);
		glLineWidth(lu5_style(&lu5)->strokeWeight);

		// Draw stroke with a larger radius
		lu5_render_cylinder_edges(
			radius + 0.5f,
			height + 0.5f,
			detail_x, detail_y,
			top_cap, 
			bottom_cap
		);
	}

	return 0;
}

int torus(lua_State *L) 
{
	lua_Number radius = lua_isnumber(L, 1) ? lua_tonumber(L, 1) : 50.0; 
	lua_Number tubeRadius = lua_isnumber(L, 2) ? lua_tonumber(L, 2) : 10.0; 

	lua_Number detail_x = lua_isnumber(L, 3) ? lua_tonumber(L, 3) : 24;
	lua_Number detail_y = lua_isnumber(L, 4) ? lua_tonumber(L, 4) : 16;

	if (lu5_has_fill()) 
	{
		lu5_apply_color(lu5_style(&lu5)->fill);
		lu5_render_torus_faces(radius, tubeRadius,
							   detail_x, detail_y);
	}

	if (lu5_has_stroke()) 
	{
		// Draw sphere edges
		lu5_apply_color(lu5_style(&lu5)->stroke);
		glLineWidth(lu5_style(&lu5)->strokeWeight);

		// Draw stroke with a larger radius
		lu5_render_torus_edges(radius, tubeRadius + 0.5f,
							   detail_x, detail_y);
	}

	return 0;
}