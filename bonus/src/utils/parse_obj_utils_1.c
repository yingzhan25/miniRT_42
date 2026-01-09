/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj_utils_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 12:09:24 by yingzhan          #+#    #+#             */
/*   Updated: 2026/01/08 12:09:25 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

int	check_texture_path(char *path)
{
	int	fd;

	if (! path || !ft_strcmp(path, "-"))
		return (0);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (1);
	close(fd);
	return (0);
}

int	parse_texture_path(char *s, t_material *ml)
{
	if (!s || !s[0])
		return (1);
	if (ft_strcmp(s, "-") != 0)
	{
		if (check_texture_path(s))
			return (1);
		ml->xpm_path = ft_strdup(s);
		if (!ml->xpm_path)
			return (1);
	}
	else
		ml->xpm_path = NULL;
	return (0);
}
