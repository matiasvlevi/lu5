#ifndef _LU5_GEOMETRY_
#define _LU5_GEOMETRY_

#define LU5_CIRCLE_SEGMENTS 36

void lu5_render_ellipse(float x, float y, float w, float h, int segments);

void lu5_render_ring(float x, float y, float inner_radius, float outer_radius, int segments);

#endif
