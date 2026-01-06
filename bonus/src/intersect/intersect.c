#include "minirt_bonus.h"

/*
** Function to compute the position along a ray at parameter t.
** The position is calculated using
** the ray equation: P(t) = origin + t * direction
*/
t_vec3	position(t_ray ray, double t)
{
	return (vec_add(ray.origin, vec_scale(ray.direction, t)));
}

/*
** Helper function to determine valid t values
** for different object types during intersection tests.
** It updates the temp_pts structure with intersection points
** and sets the appropriate t value if an intersection is found.
*/
static void	define_valid_t(t_ray *ray, t_object *current, \
	t_intersection *temp_pts, double *t)
{
	if (current->type == OBJ_SPHERE)
	{
		(*temp_pts) = ray_sphere_intersection(*ray, current->u_data.sphere);
		if ((*temp_pts).valid)
			*t = define_valid_t_for_sphere((*temp_pts).t1, (*temp_pts).t2);
	}
	if (current->type == OBJ_PLANE)
	{
		(*temp_pts) = ray_plane_intersection(*ray, current->u_data.plane);
		if ((*temp_pts).valid)
			*t = (*temp_pts).t1;
	}
	if (current->type == OBJ_CYLINDER)
	{
		(*temp_pts) = ray_cylinder_intersect(*ray, current->u_data.cylinder);
		if ((*temp_pts).valid)
			*t = define_valid_t_for_sphere((*temp_pts).t1, (*temp_pts).t2);
	}
	if (current->type == OBJ_CONE)
	{
		(*temp_pts) = ray_cone_intersect(*ray, current->u_data.cone);
		if ((*temp_pts).valid)
			*t = define_valid_t_for_sphere((*temp_pts).t1, (*temp_pts).t2);
	}
}

/*
** Helper function to loop through all objects
** in the scene and find the closest intersection.
** It updates the hit_point structure with the closest intersection details.
*/
void	object_loop(t_object *current, t_hit *hit_point, t_ray *ray)
{
	double			t;
	t_intersection	temp_pts;

	hit_point->t = INFINITY;
	while (current)
	{
		t = INFINITY;
		define_valid_t(ray, current, &temp_pts, &t);
		if (t > EPSILON && t < hit_point->t)
		{
			hit_point->t = t;
			hit_point->hit = 1;
			hit_point->object = current;
			hit_point->intersection_points = temp_pts;
		}
		current = current->next;
	}
}

/*
** Main function to find the intersection of a ray with the scene objects.
** It iterates through all objects, finds the closest
** intersection, and computes the hit point details.
** If an intersection is found, it calculates
** the hit point position and normal vector based on the object type.
*/
t_hit	intersect_object(t_ray ray, t_object *obj)
{
	t_hit		hit_point;
	t_object	*current;

	current = obj;
	ft_memset(&hit_point, 0, sizeof(t_hit));
	object_loop(current, &hit_point, &ray);
	if (hit_point.hit)
	{
		hit_point.color = hit_point.object->material.color;
		hit_point.point = position(ray, hit_point.t);
		hit_point.uv = calculate_uv(&hit_point);
		if (hit_point.object->type == OBJ_PLANE)
			hit_point.normal = hit_point.object->u_data.plane.normal;
		else if (hit_point.object->type == OBJ_SPHERE)
			hit_point.normal = vec_normalize(vec_sub(hit_point.point,
						hit_point.object->u_data.sphere.center));
		else if (hit_point.object->type == OBJ_CYLINDER)
			hit_point.normal = cylinder_normal(hit_point.point,
					hit_point.object->u_data.cylinder);
		else if (hit_point.object->type == OBJ_CONE)
			hit_point.normal = cone_normal(hit_point.point,
					hit_point.object->u_data.cone);
	}
	return (hit_point);
}
