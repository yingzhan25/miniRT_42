#include "../../includes/vector.h"

t_vec3	vec_add(t_vec3 a, t_vec3 b)
{
	t_vec3	tmp;

	tmp.x = a.x + b.x;
	tmp.y = a.y + b.y;
	tmp.z = a.z + b.z;
	return (tmp);
}

t_vec3	vec_sub(t_vec3 a, t_vec3 b)
{
	t_vec3	tmp;

	tmp.x = a.x - b.x;
	tmp.y = a.y - b.y;
	tmp.z = a.z - b.z;
	return (tmp);
}

t_vec3	vec_scale(t_vec3 v, double scalar)
{
	t_vec3	tmp;

	tmp.x = v.x * scalar;
	tmp.y = v.y * scalar;
	tmp.z = v.z * scalar;
	return (tmp);
}

t_vec3	vec_divide(t_vec3 v, double scalar)
{
	t_vec3	tmp;

	tmp.x = v.x / scalar;
	tmp.y = v.y / scalar;
	tmp.z = v.z / scalar;
	return (tmp);
}

double	vec_magnit(t_vec3 v)
{
	double	m;

	m = sqrt(v.x * v.x + v.y * v.y);
	return (m);
}

