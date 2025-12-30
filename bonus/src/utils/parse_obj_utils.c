#include "minirt_bonus.h"

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

int	parse_material_light(char *str, t_material *ml)
{
	char	**split;

	split = ft_split(str, ',');
	if (!split || (C_A_E(split) != 3) || CH_A_D(split, check_double))
		return (clean_array(split), 1);
	ml->ambient = ft_atof(split[0]);
	ml->diffuse = ft_atof(split[1]);
	ml->specular = ft_atof(split[2]);
	return (0);
}

int	parse_checkboard(char *str, t_material *ml)
{
	char	*split;

	split = ft_split(str, ',');
	if (!split || (C_A_E(split) != 2) || CH_A_D(split, check_double))
		return (clean_array(split), 1);
	ml->checker_scale = ft_atof(split[0]);
	ml->xpm_path = ft_strdup(split[1]);
	if (!ml->xpm_path)
		return (clean_array(split), 1);
	return (clean_array(split), 0);
}
