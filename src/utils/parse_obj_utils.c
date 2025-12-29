#include "minirt.h"

/*
** is_object: check whether the string
** corresponds to a known object type
*/
int	is_object(char *str)
{
	if (!str)
		return (1);
	if (!ft_strcmp(str, "pl")
		|| !ft_strcmp(str, "sp")
		|| !ft_strcmp(str, "cy"))
		return (0);
	return (1);
}

/*
** check_array_double: check whether all strings in the array are valid doubles
*/
int	check_array_double(char	**array, int (*f)(char *))
{
	int	i;

	i = 0;
	while (array[i])
	{
		if (f(array[i]))
			return (1);
		i++;
	}
	return (0);
}

/*
** parse_diametr: parse and validate a diameter value
*/
int	parse_diametr(char *s, double *diametr)
{
	if (check_double(s))
		return (1);
	*diametr = ft_atof(s);
	if (*diametr < EPSILON)
		return (1);
	return (0);
}
