#include "../../includes/vector.h"

/*
** is_zero_vec: check whether the vector is a zero vector
*/
int	is_zero_vec(t_vec3 *vec)
{
	if ((*vec).x * (*vec).x + (*vec).y * (*vec).y + (*vec).z * \
		(*vec).z < EPSILON * EPSILON)
		return (1);
	return (0);
}
