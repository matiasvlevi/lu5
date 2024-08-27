#ifndef _LU5_GEOMETRY_
#define _LU5_GEOMETRY_

#define LU5_CIRCLE_SEGMENTS 32

// 2D
void lu5_render_ellipse(float x, float y, float w, float h, int segments);
void lu5_render_ring(float x, float y, float inner_radius, float outer_radius, int segments);

void lu5_render_arc_fill(float x, float y, float w, float h, float start_angle, float end_angle, int segments);
void lu5_render_arc_stroke(float x, float y, float w, float h, float ow, float oh, float start_angle, float end_angle, int segments);
    
// 3D
void lu5_render_debug();

void lu5_render_plane_edges(float half_x, float half_y);
void lu5_render_plane_faces(float half_x, float half_y);

void lu5_render_ellipsoid_faces(float radius, int detail_x, int detail_y);
void lu5_render_ellipsoid_edges(float radius, int detail_x, int detail_y);

void lu5_render_box_faces(float width, float height, float depth);
void lu5_render_box_edges(float width, float height, float depth);

#endif
