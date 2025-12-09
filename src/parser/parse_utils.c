#include "scene.h"

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
 * Receive ONLY input with correct dot format and numeric(sign allowd);
 * convert string to double;
 * possible to have overflow
 */
double	ft_atof(const char *str)
{
	double	sign;
	double	integer;
	double	fraction;
	double	divisor;
	int		i;

	sign = 1.0;
	integer = 0.0;
	fraction = 0.0;
	divisor = 1.0;
	i = 0;
	if (str[i] == '-')
	{
		sign = -1.0;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] && str[i] != '.')
	{
		integer = 10 * integer + (str[i] - '0');
		i++;
	}
	i++;
	while (str[i])
	{
		fraction = 10 * fraction + (str[i] - '0');
		divisor *= 10;
		i++;
	}
	return (sign * (integer + fraction / divisor));
}

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
 * check whether is numeric (sign not allowed, negative not allowed)
 */
int	check_int(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (ft_putstr_fd("Error/nAmbient: ", 2), ft_putchar_fd(c, 2), ft_putstr_fd(": Invalid input\n", 2), 1);
		i++;
	}
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
