/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 12:36:30 by yingzhan          #+#    #+#             */
/*   Updated: 2026/01/09 14:11:33 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	count_array_element(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

/**
 * Clean up memory allocated by ft_split()
 */
void	clean_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

/**
 * Check multiple dots and return position of "." in a string;
 * applied for both filename and double number;
 * filename:
 * check if (!ret || ret == -1 || ret == len - 1):
 * should be at least 1 dot and it should not be positioned at the start or end;
 * double:
 * check if (!ret || ret == len - 1):
 * should not be positioned at the start or end;
 * can be without dot
 */
int	check_dot(char *s)
{
	int	pos;
	int	i;

	pos = -1;
	i = 0;
	while (s[i])
	{
		if (s[i] == '.')
		{
			if (pos != -1)
				return (-1);
			pos = i;
		}
		i++;
	}
	return (pos);
}

/**
 * Check whether the scene file has a valid filename and ends with ".rt";
 * edge cases:
 * .rt is unvalid filename;
 * filename with multiple .(path) is valid
 */
int	check_extension(char *s1, char *s2)
{
	char	*last_dot_pos;

	if (!s1 || !s1[0])
		return (1);
	last_dot_pos = ft_strrchr(s1, '.');
	if (!last_dot_pos || last_dot_pos == s1 || ft_strcmp(last_dot_pos, s2))
		return (1);
	return (0);
}
