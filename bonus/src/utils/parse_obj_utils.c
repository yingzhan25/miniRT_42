/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 12:09:32 by yingzhan          #+#    #+#             */
/*   Updated: 2026/01/08 12:09:33 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		|| !ft_strcmp(str, "cy")
		|| !ft_strcmp(str, "co"))
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

int	parse_shineness(char *s, double *shineness)
{
	if (check_double(s))
		return (1);
	*shineness = ft_atof(s);
	if (*shineness < SHINENESS_MIN || *shineness > SHINENESS_MAX)
		return (1);
	return (0);
}

int	parse_texture_type(char *s, t_texture_type *type)
{
	int	i;

	if (check_int(s))
		return (1);
	i = ft_atoi(s);
	if ((0 > i) || (i > 2))
		return (1);
	if (i == 0)
		*type = TEXTURE_NONE;
	else if (i == 1)
		*type = TEXTURE_CHECKER;
	else
		*type = TEXTURE_XPM;
	return (0);
}
