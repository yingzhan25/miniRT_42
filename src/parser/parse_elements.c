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
		return (error("Ambient: ratio: Invalid input\n"), 1);
	i = 0;
	if (s[i] == '-' || s[i] == '+')
		i++;
	while (s[i])
	{
		if (i != dot_pos && !ft_isdigit(s[i]))
			return (error("Ambient: ratio: Invalid input\n"), 1);
		i++;
	}
	scene->ambient.ratio = ft_atof(s);
	if (scene->ambient.ratio < RATIO_MIN || scene->ambient.ratio > RATIO_MAX)
		return (error("Ambient: ratio: Exceed valid range\n"), 1);
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
		return (error("Memory allocation failed\n"), 1);
	if (count_array_element(arr) != 3 || !arr[0] || !arr[1] || !arr[2])
		return (error("Ambient: RGB: Invalid input\n"), clean_array(arr), 1);
//	printf("arr[0]: %s/n", arr[0]);
	if (check_int(arr[0], 'R') || check_int(arr[1], 'G') || check_int(arr[2], 'B'))
		return (clean_array(arr), 1);
	scene->ambient.color.r = ft_atoi(arr[0]);
	if (scene->ambient.color.r > RGB_MAX)
		return (error("Ambient: R: Exceed valid range\n"), clean_array(arr), 1);
	scene->ambient.color.g = ft_atoi(arr[1]);
	if (scene->ambient.color.g > RGB_MAX)
		return (error("Ambient: G: Exceed valid range\n"), clean_array(arr), 1);
	scene->ambient.color.b = ft_atoi(arr[2]);
	if (scene->ambient.color.b > RGB_MAX)
		return (error("Ambient: B: Exceed valid range\n"), clean_array(arr), 1);
	return (clean_array(arr), 0);
}