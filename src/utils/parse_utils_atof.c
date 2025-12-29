#include "minirt.h"

static double	skip_sign(const char *str, int *i)
{
	double	sign;

	sign = 1.0;
	*i = 0;
	while (str[*i] == ' ' || str[*i] == '\t' || \
			str[*i] == '\n' || str[*i] == '\r' || \
			str[*i] == '\f' || str[*i] == '\v')
		(*i)++;
	if (str[*i] == '-')
	{
		sign = -1.0;
		(*i)++;
	}
	else if (str[*i] == '+')
		(*i)++;
	return (sign);
}

static void	calc_fraction(const char *str, int *i, double *frac, double *div)
{
	(*i)++;
	while (str[*i])
	{
		if (str[*i] < '0' || str[*i] > '9')
			break ;
		*frac = 10 * (*frac) + (str[*i] - '0');
		*div *= 10;
		(*i)++;
	}
}

/**
 * Receive input with or without dot and numeric(sign allowd);
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

	integer = 0.0;
	fraction = 0.0;
	divisor = 1.0;
	sign = skip_sign(str, &i);
	while (str[i] && str[i] != '.')
	{
		if (str[i] < '0' || str[i] > '9')
			break ;
		integer = 10 * integer + (str[i] - '0');
		i++;
	}
	if (str[i] == '.')
		calc_fraction(str, &i, &fraction, &divisor);
	return (sign * (integer + fraction / divisor));
}
