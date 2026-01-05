#include "minirt_bonus.h"

t_color	calculate_checker(t_vec3 hit_to_point, t_vec3 u_axis, t_vec3 v_axis)
{
	double	u;
	double	v;
	int		i;
	int		j;

	u = dot_product(hit_to_point, u_axis);
	v = dot_product(hit_to_point, v_axis);
	i = (int)floor(u / CHECKER_SCALE);
	j = (int)floor(v / CHECKER_SCALE);
	if ((i + j) % 2)
		return ((t_color)CHECKER_COLOR1);
	return ((t_color)CHECKER_COLOR2);
}

/**
 * Calculate checkered texture for plane;
 * set up a world coordinate based on plane normal;
 * find out projection of vecter in u and v axis;
 * using floor() to find the small roundup number after divide scale;
 * decide in which color of checker
 */
t_color	get_texture_color(t_hit *hit)
{
	t_vec3	u_axis;
	t_vec3	v_axis;
	t_vec3	tmp_up;
	t_vec3	hit_to_point;

	if (fabs(hit->normal.y) > 1.0 - EPSILON)
		tmp_up = (t_vec3){0, 0, 1};
	else
		tmp_up = (t_vec3){0, 1, 0};
	u_axis = vec_normalize(vec_cross(tmp_up, hit->normal));
	v_axis = vec_normalize(vec_cross(hit->normal, u_axis));
	hit_to_point = vec_sub(hit->point, hit->object->u_data.plane.point);
	return (calculate_checker(hit_to_point, u_axis, v_axis));
}
