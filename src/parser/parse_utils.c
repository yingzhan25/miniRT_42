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
 * Check whether the scene file has a valid filename and ends with ".rt";
 * multiple entension(more than 1 dots) is forbidden
 */
int check_extension(char *s1, char *s2)
{
	int pos;
	int len;

	if (!s1 || !s1[0])
		return (1);
	pos = check_dot(s1);
	len = ft_strlen(s1);
	if (!pos || pos == -1 || pos == len - 1)
		return (1);
	if (len <= (int)ft_strlen(s2) || ft_strcmp(s1 + len - (int)ft_strlen(s2), s2))
		return (1);
	return (0);
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
