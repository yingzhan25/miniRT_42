#ifndef VECTOR_H
# define VECTOR_H

# include <math.h>
# include <float.h>

// Small value to prevent division by zero
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
t_vec3	vec_cross(t_vec3 a, t_vec3 b);
t_vec3	vec_normalize(t_vec3 v);
t_vec3	vec_negate(t_vec3 v);
t_vec3	vec_new(double x, double y, double z);
double	vec_length(t_vec3 v);
double	dot_product(t_vec3 a, t_vec3 b);
int		is_zero_vec(t_vec3 *vec);


#endif
