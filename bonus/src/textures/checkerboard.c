#include "minirt_bonus.h"

/**
 * Calculate checkered texture for objects;
 * i, j: index of checkerboard;
 * using floor() to find the small roundup index after divide scale;
 * decide the color of checker with (i + j) % 2
 * the scale of plane should be larger than sphere,
 * because plane uv is not normalized
 */
t_color	get_cb_color(t_hit *hit)
{
	int		i;
	int		j;

	if (hit->object->type == OBJ_PLANE)
	{
		i = (int)floor(hit->uv.u / SCALE_S);
		j = (int)floor(hit->uv.v / SCALE_S);
		if ((i + j) % 2)
			return ((t_color)RED);
		return ((t_color)BLUE);
	}
	else
	{
		i = (int)floor(hit->uv.u / SCALE_L);
		j = (int)floor(hit->uv.v / SCALE_L);
		if ((i + j) % 2)
			return ((t_color)BLACK);
		return ((t_color)WHITE);
	}
}
