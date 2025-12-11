#include "scene.h"

/**
 * Check whether is valid double;
 * Check whether is in the valid range;
 * convert to double and update ambient.ratio
 */
int	parse_ratio(char *s, t_scene *scene)
{
	if (check_double(s))
		return (error(A_INVL_RATIO), 1);
	scene->ambient.ratio = ft_atof(s);
	if (scene->ambient.ratio < RATIO_MIN || scene->ambient.ratio > RATIO_MAX)
		return (error(A_EXCD_RATIO), 1);
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
		return (error(FAIL_MEM_ALLOC), 1);
	if (count_array_element(arr) != 3 || !arr[0] || !arr[1] || !arr[2])
		return (error(A_INVL_COLOR), clean_array(arr), 1);
//	printf("arr[0]: %s/n", arr[0]);
	if (check_int(arr[0]) || check_int(arr[1]) || check_int(arr[2]))
		return (error(A_INVL_COLOR), clean_array(arr), 1);
	scene->ambient.color.r = ft_atoi(arr[0]);
	scene->ambient.color.g = ft_atoi(arr[1]);
	scene->ambient.color.b = ft_atoi(arr[2]);
	if (scene->ambient.color.r > RGB_MAX || scene->ambient.color.g > RGB_MAX ||scene->ambient.color.b > RGB_MAX)
		return (error(A_EXCD_COLOR), clean_array(arr), 1);
	return (clean_array(arr), 0);
}

/**
 * Check whether the number of entry is correct and elements are not empty;
 * check whether the information is redefined (once defined, no matter succeed or not, cannot be redefined);
 * check whether the ratio is valid;
 * check whether the RGB is valid
 */
int	parse_ambient(char **array, t_scene *scene)
{
	if (scene->num_a)
		return (error(A_MULTIPLE_DEF), 1);
	scene->num_a = 1;
	if (!array || count_array_element(array) != 3 || !array[0] || !array[1] || !array[2])
		return (error(INVALID_A_ARG), 1);
	return (parse_ratio(array[1], scene) || parse_colors(array[2], scene));
}
