#include "../../includes/vector.h"

/*
** is_zero_vec: check whether the vector is a zero vector
*/
int	is_zero_vec(t_vec3 *vec)
{
	if ((*vec).x == 0 && (*vec).y == 0 && (*vec).z == 0)
        return (1);
	return (0);
}