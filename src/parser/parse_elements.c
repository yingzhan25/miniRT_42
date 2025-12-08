#include "scene.h"

int	count_array_element(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

int	parse_ambient(char **array, t_scene *scene)
{
	if (!array || count_array_element(array) != 3 || !array[0] || !array[1] || !array[2])
		return (ft_putstr_fd("Error/nAmbient: Usage: A Ratio [r,g,b]\n", 2), 1);
	if (scene->num_a)
		return (ft_putstr_fd("Error/nAmbient: more than 1 definition\n", 2), 1);
	if (parse_doubles(array[1], scene))
		return (1);
	//parse_rgb
}