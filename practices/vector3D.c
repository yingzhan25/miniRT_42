// 1. Sub-problem (Points in 3D Space)

// Requirement: to represent vectors

// Create a 3D vector struct that support following operations:

//     Vector Addition
//     Vector Subtraction
//     Vector Magnitude
//     Dot Product
//     Vector Normalization
//     Vector Multiplication (Multiplying a Vector by a scalar)

#include <math.h>

typedef	struct s_vector
{
	float	x;
	float	y;
	float	z;
}	t_vector;

t_vector	addition(t_vector a, t_vector b)
{
	t_vector	ret;

	ret.x = a.x + b.x;
	ret.y = a.y + b.y;
	ret.z = a.z + b.z;
	return (ret);
}

t_vector	subtraction(t_vector a, t_vector b)
{
	t_vector	ret;

	ret.x = a.x - b.x;
	ret.y = a.y - b.y;
	ret.z = a.z - b.z;
	return (ret);
}

float	magnitude(t_vector	v)
{
	float	m;

	m = sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
	return (m);
}

float	dot_product(t_vector a, t_vector b)
{
	float	product;

	product = a.x * b.x + a.y * b.y + a.z * b.z;
	return (product);
}

t_vector	normalization(t_vector v)
{
	float	m;
	t_vector	ret;

	m = magnitude(v);
	if (m == 0.0f)
	{
		ret.x = 0.0f;
		ret.y = 0.0f;
		ret.z = 0.0f;
	}
	else
	{
		ret.x = v.x / m;
		ret.y = v.y / m;
		ret.z = v.z / m;
	}
	return (ret);
}

t_vector	multiplication(t_vector v, float scale)
{
	t_vector	ret;

	ret.x = v.x * scale;
	ret.y = v.y * scale;
	ret.z = v.z * scale;
	return (ret);
}