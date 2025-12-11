#include "../../includes/minirt.h"


/*
** is_object: check whether the string 
** corresponds to a known object type
*/
int	is_object(char *str)
{
	if (!str)
		return (1);
	if (!ft_strcmp(str, "pl")
		|| ft_strcmp(str, "sp")
		|| ft_strcmp(str, "cy"))
		return (0);
	return (1);
}
