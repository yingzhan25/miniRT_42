#include "minirt_bonus.h"

/**
 * convert 3d hit point on the surface of plane into 2d coordinates
 * set up a world coordinate based on plane normal;
 * calculate u and v axis with cross product, normalize to unit vector;
 * get vector from plane point to hit point;
 * find out projection of vecter in u and v axis with dot product
 */
static t_uv	plane_uv(t_vec3 point, t_plane plane, t_hit *hit)
{
	t_vec3	tmp_up;
	t_axis	axis;
	t_uv	uv;
	t_vec3	p;

	if (fabs(hit->normal.y) > 1.0 - EPSILON)
		tmp_up = (t_vec3){0, 0, 1};
	else
		tmp_up = (t_vec3){0, 1, 0};
	axis.u_axis = vec_normalize(vec_cross(tmp_up, hit->normal));
	axis.v_axis = vec_normalize(vec_cross(hit->normal, axis.u_axis));
	p = vec_sub(point, plane.point);
	uv.u = dot_product(p, axis.u_axis);
	uv.v = dot_product(p, axis.v_axis);
	return (uv);
}

/*
** convert 3d hit point on the surface of sphere into 2d coordinates
** get vector from sphere center to hit point
** normalize to unit sphere
** convert to spherical coordinates:
**    - u: azimuthal angle (horizontal wrap around sphere)
**    - v: polar angle (vertical from top to bottom)
*/

static t_uv	sphere_uv(t_vec3 point, t_sphere sphere)
{
	t_uv	uv;
	t_vec3	p;

	p = vec_sub(point, sphere.center);
	p = vec_normalize(p);
	uv.u = 0.5 + atan2(p.z, p.x) / (2 * M_PI);
	uv.v = 0.5 - asin(p.y) / M_PI;
	return (uv);
}

/*
** convert 3d hit point to 2d texture coordinates
*/
t_uv	calculate_uv(t_hit *hit)
{
	t_uv	uv;

	uv.u = 0.0;
	uv.v = 0.0;
	if (hit->object->material.texture == TEXTURE_NONE)
		return (uv);
	if (hit->object->type == OBJ_SPHERE)
		return (sphere_uv(hit->point, hit->object->u_data.sphere));
	else if (hit->object->type == OBJ_PLANE)
		return (plane_uv(hit->point, hit->object->u_data.plane, hit));
	return (uv);
}
