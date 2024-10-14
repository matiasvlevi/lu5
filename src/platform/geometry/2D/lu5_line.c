#include "../../../lu5_geometry.h"
#include "../../../lu5_color.h"

#include <math.h>

void lu5_render_line(
    lua_Number x1, lua_Number y1, 
    lua_Number x2, lua_Number y2,
    lua_Number weight,
    lu5_color color)
{
	float dx = x2 - x1;
	float dy = y2 - y1;
	float length = sqrt(dx * dx + dy * dy);

	float nx = weight * ( dy / length);
	float ny = weight * (-dx / length);

	if (lu5_color_visible(color)) 
	{
		lu5_render_quad(
			x1 - nx, y1 - ny,
			x1 + nx, y1 + ny,
			x2 + nx, y2 + ny,
			x2 - nx, y2 - ny,
            weight,
            color,
			LU5_RGBA(0, 0, 0, 0));

		if (weight >= 3) 
		{
			lu5_render_ellipse_fill(x1, y1, 
				weight, weight, 
				color,
				LINE_POINT_SEGMENTS);

			lu5_render_ellipse_fill(x2, y2, 
				weight, weight,  
				color,
				LINE_POINT_SEGMENTS);
		};
	}
}