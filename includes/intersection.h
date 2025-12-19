#ifndef INTERSECTION_H
# define INTERSECTION_H

# include "minirt.h"

typedef struct	s_intersection
{
	double	t1;
	double	t2;
}	t_intersection;

typedef struct s_hit {
	int			hit;            // Did the ray hit anything?
	double		t;            // Distance along ray to hit point
	t_vec3		point;        // 3D hit point
	t_vec3		normal;       // Surface normal at hit point (normalized)
	t_object	*object;    // Pointer to the hit object
	t_color		color;       // Object color at hit point
}	t_hit;

#endif