#ifndef VECTOR_H
# define VECTOR_H

# include <math.h>
# include <float.h>

# define EPSILON 1.0e-6
// Core vector type for 3D coordinates, directions, and colors
typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}		t_vec3;
#define ZERO_VECTOR (t_vec3){0.0, 0.0, 0.0}

t_vec3	vec_add(t_vec3 a, t_vec3 b);
t_vec3	vec_sub(t_vec3 a, t_vec3 b);
t_vec3	vec_scale(t_vec3 v, double scalar);
t_vec3	vec_divide(t_vec3 v, double scalar);
double	vec_magnit(t_vec3 v);

#endif
