#include "scene.h"

/**
 * Check whether dot format is correct;
 * check whether is numeric (sign allowed);
 * check whether is in the valid range;
 * convert to double and update ambient.ratio
 */
int	parse_doubles(char *s, t_scene *scene)
{
	int		dot_pos;
	int		i;

	dot_pos = check_dot(s);
	if (!dot_pos || dot_pos == (int)ft_strlen(s) - 1)
		return (ft_putstr_fd("Error/nAmbient: ratio: Invalid input\n", 2), 1);
	i = 0;
	if (s[i] == '-' || s[i] == '+')
		i++;
	while (s[i])
	{
		if (i != dot_pos && !ft_isdigit(s[i]))
			return (ft_putstr_fd("Error/nAmbient: ratio: Invalid input\n", 2), 1);
		i++;
	}
	scene->ambient.ratio = ft_atof(s);
	if (scene->ambient.ratio < RATIO_MIN || scene->ambient.ratio > RATIO_MAX)
		return (ft_putstr_fd("Error/nAmbient: ratio: Exceed valid range\n", 2), 1);
	return (0);
}

/**
 * Check whether the number of entry is correct and elements are not empty;
 * check whether is numeric (sign not allowed, negative not allowed);
 * check whether is in the valid range;
 * convert to int and update ambient.color;
 * clean up memory before return
 */
int	parse_colors(char *s, t_scene *scene)
{
	char	**arr;

	arr = ft_split(s, ',');
	if (!arr)
		return (ft_putstr_fd("Error/nMemory allocation failed\n", 2), 1);
	if (count_array_element(arr) != 3 || !arr[0] || !arr[1] || !arr[2])
		return (ft_putstr_fd("Error/nAmbient: RGB: Invalid input\n", 2), clean_array(arr), 1);
	if (check_int(arr[0], 'R') || check_int(arr[1], 'G') || check_int(arr[2], 'B'))
		return (clean_array(arr), 1);
	scene->ambient.color.x = ft_atoi(arr[0]);
	if (scene->ambient.color.x > RGB_MAX)
		return (ft_putstr_fd("Error/nAmbient: R: Exceed valid range\n", 2), clean_array(arr), 1);
	scene->ambient.color.y = ft_atoi(arr[1]);
	if (scene->ambient.color.y > RGB_MAX)
		return (ft_putstr_fd("Error/nAmbient: G: Exceed valid range\n", 2), clean_array(arr), 1);
	scene->ambient.color.z = ft_atoi(arr[2]);
	if (scene->ambient.color.z > RGB_MAX)
		return (ft_putstr_fd("Error/nAmbient: B: Exceed valid range\n", 2), clean_array(arr), 1);
	return (clean_array(arr), 0);
}