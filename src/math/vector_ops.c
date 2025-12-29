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

/*
** here is the thing that if scalar value is eqaual to 0, we should 
** return the error. its good to check before calling the function, i think so
** it would be more safer than returning zero vector 
*/
t_vec3	vec_divide(t_vec3 v, double scalar)
{
	t_vec3	tmp;

	if (scalar < EPSILON)
		return (vec_zero());
	tmp.x = v.x / scalar;
	tmp.y = v.y / scalar;
	tmp.z = v.z / scalar;
	return (tmp);
}

t_vec3	vec_new(double x, double y, double z)
{
	t_vec3 tmp;

	tmp.x = x;
	tmp.y = y;
	tmp.z = z;
	return (tmp);
}
