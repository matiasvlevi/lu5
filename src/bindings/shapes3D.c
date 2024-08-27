
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

	if (lu5.style.fill.a != 0.0f) {
		lu5_apply_color(lu5.style.fill);
		
		lu5_render_plane_faces(half_x, half_y);
	}

	if (lu5.style.stroke.a != 0.0f) {
		lu5_apply_color(lu5.style.stroke);
		glLineWidth(lu5.style.strokeWeight);
		
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

	if (lu5.style.fill.a != 0.0f) {
		lu5_apply_color(lu5.style.fill);
		
		lu5_render_box_faces(w, h, d);
	}

	if (lu5.style.stroke.a != 0.0f) {
		lu5_apply_color(lu5.style.stroke);
		glLineWidth(lu5.style.strokeWeight);

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

	if (lu5.style.fill.a != 0.0f) {
		lu5_apply_color(lu5.style.fill);
		lu5_render_ellipsoid_faces(radius, detail_x, detail_y);
	}

	if (lu5.style.stroke.a != 0.0f) {
		// Draw sphere edges
		lu5_apply_color(lu5.style.stroke);
		glLineWidth(lu5.style.strokeWeight);

		// Draw stroke with a larger radius
		lu5_render_ellipsoid_edges(
			radius + 1.0f,
			detail_x, detail_y
		);
	}

	return 0;
}

int debugMode(lua_State *L)
{
	lu5_render_debug();

	return 0;
}