#include "minirt.h"

/**
 * Check whether is valid double;
 * Check whether is in the valid range;
 * convert to double and update ratio
 */
int	parse_ratio(char *s, double *ratio)
{
	if (check_double(s))
		return (1);
	*ratio = ft_atof(s);
	if (*ratio < RATIO_MIN || *ratio > RATIO_MAX)
		return (1);
	return (0);
}

/**
 * Check whether the number of entry is correct and elements are not empty;
 * check whether is numeric (sign not allowed, negative not allowed);
 * check whether is in the valid range;
 * convert to int and update color;
 * clean up memory before return
 */
int	parse_colors(char *s, t_color *color)
{
	char	**arr;

	arr = ft_split(s, ',');
	if (!arr)
		return (error(FAIL_MEM_ALLOC), 1);
	if (C_A_E(arr) != 3 || !arr[0] || !arr[1] || !arr[2])
		return (clean_array(arr), 1);
	if (check_int(arr[0]) || check_int(arr[1]) || check_int(arr[2]))
		return (clean_array(arr), 1);
	(*color).r = ft_atoi(arr[0]);
	(*color).g = ft_atoi(arr[1]);
	(*color).b = ft_atoi(arr[2]);
	if ((*color).r > RGB_MAX || (*color).g > RGB_MAX || (*color).b > RGB_MAX)
		return (clean_array(arr), 1);
	return (clean_array(arr), 0);
}

/**
 * Check whether the number of entry is correct and elements are not empty;
 * check whether the information is redefined
 * (once defined, no matter succeed or not, cannot be redefined);
 * check whether the ratio is valid;
 * check whether the RGB is valid
 */
int	parse_ambient(char **array, t_scene *scene)
{
	double	ratio;
	t_color	color;

	if (scene->num_a)
		return (error(A_MULTIPLE_DEF), 1);
	scene->num_a = 1;
	if (!array || C_A_E(array) != 3 || !array[0] || !array[1] || !array[2])
		return (error(A_INVL_ARG), 1);
	if (P_RAT(array[1], &ratio))
		return (error(A_INVL_RATIO), 1);
	if (P_COL(array[2], &color))
		return (error(A_INVL_COLOR), 1);
	scene->ambient.ratio = ratio;
	scene->ambient.color = color;
	return (0);
}
