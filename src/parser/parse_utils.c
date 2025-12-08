#include "scene.h"

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

int	count_dot(char *s)
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
	}
	return (pos);
}

int	parse_double(char *s, t_scene *scene)
{
	int	dot_pos;
	int	i;

	dot_pos = count_dot(s);
	if (dot_pos == -1 || !dot_pos || dot_pos == ft_strlen(s) - 1)
		return (ft_putstr_fd("Error/nAmbient: Invalid double\n", 2), 1);
	i = 0;
	while (s[i])
	{
		if (i != dot_pos && !ft_isdigit(s[i]))
			return (ft_putstr_fd("Error/nAmbient: Invalid double\n", 2), 1);
		i++;
	}
	//atof
	return (0);
}