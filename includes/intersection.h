#ifndef INTERSECTION_H
# define INTERSECTION_H

# include "minirt.h"

typedef struct	s_intersection
{
	int		valid;
	double	t1;
	double	t2;
}	t_intersection;

typedef struct s_hit {
	int			hit;            // Did the ray hit anything?
	t_intersection	intersection_points;
	double		t;
	t_vec3		point;        // 3D hit point
	t_vec3		normal;       // Surface normal at hit point (normalized)
	t_object	*object;    // Pointer to the hit object
	t_color		color;       // Object color at hit point
}	t_hit;

t_intersection	ray_sphere_intersection(t_ray ray, t_sphere sphere);
double			define_valid_t_for_sphere(double t1, double t2);
t_hit			intersect_object(t_ray ray, t_object *obj);
t_intersection	ray_plane_intersection(t_ray ray);

// Lighting and shade
t_color			calculate_color(t_hit *hit, t_scene *scene);
void			calculate_ambient(t_color *color, t_hit *hit, t_scene *scene);
void			calculate_diffuse(t_color *color, t_vec3 hit_to_light, t_hit *hit, t_scene *scene);


#endif