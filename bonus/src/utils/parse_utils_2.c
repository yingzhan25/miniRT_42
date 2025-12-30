#include "minirt_bonus.h"

/**
 * Free all the memory allocated on the heap
 */
void	free_scene(t_scene *scene)
{
	t_object	*next;

	if (!scene)
		return ;
	while (scene->objects)
	{
		next = scene->objects->next;
		free (scene->objects);
		scene->objects = next;
	}
	free (scene);
}

/**
 * Check whether dot format is correct;
 * check whether is numeric (sign allowed);
 */
int	check_double(char *s)
{
	int		dot_pos;
	int		i;

	dot_pos = check_dot(s);
	if (!dot_pos || dot_pos == (int)ft_strlen(s) - 1)
		return (1);
	i = 0;
	if (s[i] == '-' || s[i] == '+')
		i++;
	while (s[i])
	{
		if (i != dot_pos && !ft_isdigit(s[i]))
			return (1);
		i++;
	}
	return (0);
}

/**
 * check whether is numeric (sign not allowed, negative not allowed)
 */
int	check_int(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (1);
		i++;
	}
	return (0);
}

/**
 * Error\nAmbient: ratio: invalid double\n
 */
void	error(char *msg)
{
	ft_putstr_fd(ERROR_MESSAGE, 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
}
