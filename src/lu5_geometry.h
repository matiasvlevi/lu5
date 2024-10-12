#ifndef _LU5_GEOMETRY_
#define _LU5_GEOMETRY_

#include "lu5_decorators.h"
#include "lu5_window.h"
#include "lu5_color.h"

#include <lua.h>

#include "lu5_geometry_core.h"


WASM_IMPORT("env", "lu5_render_ellipse") 
void lu5_render_ellipse(
    lua_Number x, lua_Number y, 
    lua_Number w, lua_Number h,
    lu5_color color,
    lua_Integer segments);

WASM_IMPORT("env", "lu5_render_triangle_fill")
void lu5_render_triangle_fill(
    lua_Number x1, lua_Number y1,
    lua_Number x2, lua_Number y2,
    lua_Number x3, lua_Number y3,
    lu5_color color);

WASM_IMPORT("env", "lu5_render_arc_fill")
void lu5_render_arc_fill(
    lua_Number x, lua_Number y, 
    lua_Number w, lua_Number h, 
    lua_Number start_angle, 
    lua_Number end_angle, 
    lua_Integer segments,
    lu5_color color);

WASM_IMPORT("env", "lu5_render_arc_stroke")
void lu5_render_arc_stroke(
    lua_Number x, lua_Number y, 
    lua_Number w, lua_Number h, 
    lua_Number strokeWeight,
    lua_Number start_angle, 
    lua_Number end_angle, 
    lua_Integer segments,
    lu5_color color);

WASM_IMPORT("env", "lu5_render_quad")
void lu5_render_quad(
    lua_Number x1, lua_Number y1,
    lua_Number x2, lua_Number y2,
    lua_Number x3, lua_Number y3,
    lua_Number x4, lua_Number y4,
    lua_Number strokeWeight,
    lu5_color fill,
    lu5_color stroke);

WASM_IMPORT("env", "lu5_render_line")
void lu5_render_line(
    lua_Number x1, lua_Number y1, 
    lua_Number x2, lua_Number y2,
    lua_Number weight,
    lu5_color color);


// Non-standard format, since it takes in fill & stroke
// This may be preferable for WASM since we would call once per shape instead of twice
WASM_IMPORT("env", "lu5_render_ellipse_w_stroke") 
void lu5_render_ellipse_w_stroke(
    lua_Number x, lua_Number y,
    lua_Number w, lua_Number h,
    lua_Number strokeWeight,
    lu5_color fill,
    lu5_color stroke,
    lua_Integer segments);


// 3D
WASM_IMPORT("env", "lu5_render_debug")
void lu5_render_debug();

WASM_IMPORT("env", "lu5_render_plane_edges")
void lu5_render_plane_edges(
    lua_Number half_x, lua_Number half_y, 
    lu5_color color);

WASM_IMPORT("env", "lu5_render_plane_faces")
void lu5_render_plane_faces(
    lua_Number half_x, lua_Number half_y, 
    lu5_color color);

WASM_IMPORT("env", "lu5_render_ellipsoid_faces")
void lu5_render_ellipsoid_faces(
    lua_Number radius, 
    lua_Integer detail_x, 
    lua_Integer detail_y, 
    lu5_color color);

WASM_IMPORT("env", "lu5_render_ellipsoid_edges")
void lu5_render_ellipsoid_edges(
    lua_Number radius, 
    lua_Integer detail_x, 
    lua_Integer detail_y, 
    lu5_color color);

WASM_IMPORT("env", "lu5_render_box_faces")
void lu5_render_box_faces(
    lua_Number width, 
    lua_Number height, 
    lua_Number depth, 
    lu5_color color);

WASM_IMPORT("env", "lu5_render_box_edges")
void lu5_render_box_edges(
    lua_Number width, 
    lua_Number height, 
    lua_Number depth, 
    lu5_color color);

WASM_IMPORT("env", "lu5_render_cylinder_edges")
void lu5_render_cylinder_edges(
    lua_Number radius, 
    lua_Number height, 
    lua_Integer detail_x, 
    lua_Integer detail_y, 
    bool bottom_cap, 
    bool top_cap, 
    lu5_color color);

WASM_IMPORT("env", "lu5_render_cylinder_faces")
void lu5_render_cylinder_faces(
    lua_Number radius, 
    lua_Number height, 
    lua_Integer detailX, 
    lua_Integer detailY, 
    bool bottom_cap, 
    bool top_cap, 
    lu5_color color);

WASM_IMPORT("env", "lu5_render_torus_faces")
void lu5_render_torus_faces(
    lua_Number radius, 
    lua_Number tubeRadius, 
    lua_Integer detailX, 
    lua_Integer detailY, 
    lu5_color color);

WASM_IMPORT("env", "lu5_render_torus_edges")
void lu5_render_torus_edges(
    lua_Number radius, 
    lua_Number tubeRadius, 
    lua_Integer detailX, 
    lua_Integer detailY, 
    lu5_color color);

#endif
