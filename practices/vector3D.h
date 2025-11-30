#ifndef VECTOR3D_H
#define VECTOR3D_H

#include <math.h>

typedef	struct s_vector
{
	float	x;
	float	y;
	float	z;
}	t_vector;

t_vector	addition(t_vector a, t_vector b);
t_vector	subtraction(t_vector a, t_vector b);
float		magnitude(t_vector	v);
float		dot_product(t_vector a, t_vector b);
t_vector	normalization(t_vector v);
t_vector	multiplication(t_vector v, float scale);

#endif