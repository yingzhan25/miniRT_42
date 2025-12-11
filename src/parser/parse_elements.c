#include "scene.h"

/**
 * Check whether is valid double;
 * Check whether is in the valid range;
 * convert to double and update ambient.ratio
 */
int	parse_ratio(char *s, t_scene *scene, char *name, char *sub_name)
{
	if (check_double(s, name, sub_name))
		return (1);
	scene->ambient.ratio = ft_atof(s);
	if (scene->ambient.ratio < RATIO_MIN || scene->ambient.ratio > RATIO_MAX)
		return (error(name, sub_name, "Exceed valid range\n"), 1);
	return (0);
}

/**
 * Check whether the number of entry is correct and elements are not empty;
 * check whether is numeric (sign not allowed, negative not allowed);
 * check whether is in the valid range;
 * convert to int and update ambient.color;
 * clean up memory before return
 */
int	parse_colors(char *s, t_scene *scene, char *name, char *sub_name)
{
	char	**arr;

	arr = ft_split(s, ',');
	if (!arr)
		return (error(name, sub_name, "Memory allocation failed\n"), 1);
	if (count_array_element(arr) != 3 || !arr[0] || !arr[1] || !arr[2])
		return (error(name, sub_name, "Invalid input\n"), clean_array(arr), 1);
//	printf("arr[0]: %s/n", arr[0]);
	if (check_int(arr[0], name, "R") || check_int(arr[1], name, "G") || check_int(arr[2], name, "B"))
		return (clean_array(arr), 1);
	scene->ambient.color.r = ft_atoi(arr[0]);
	if (scene->ambient.color.r > RGB_MAX)
		return (error(name, "R", "Exceed valid range\n"), clean_array(arr), 1);
	scene->ambient.color.g = ft_atoi(arr[1]);
	if (scene->ambient.color.g > RGB_MAX)
		return (error(name, "G", "Exceed valid range\n"), clean_array(arr), 1);
	scene->ambient.color.b = ft_atoi(arr[2]);
	if (scene->ambient.color.r > RGB_MAX || scene->ambient.color.g > RGB_MAX ||scene->ambient.color.b > RGB_MAX)
		return (error(name, "B", "Exceed valid range\n"), clean_array(arr), 1);
	return (clean_array(arr), 0);
}

int	parse_tuples(char *s, t_scene *scene, char *name, char *sub_name)
{
	char	**arr;

	arr = ft_split(s, ',');
	if (!arr)
		return (error(name, sub_name, "Memory allocation failed\n"), 1);
	if (count_array_element(arr) != 3 || !arr[0] || !arr[1] || !arr[2])
		return (error(name, sub_name, "Invalid input\n"), clean_array(arr), 1);
	if (check_double(arr[0], name, "x") || check_double(arr[1], name, "y") || check_double(arr[2], name, "z"))
		return (clean_array(arr), 1);
	scene->camera.position.x = ft_atof(arr[0]);
	scene->camera.position.y = ft_atof(arr[1]);
	scene->camera.position.z = ft_atof(arr[2]);
	return (0);
}