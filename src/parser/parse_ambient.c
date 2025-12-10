#include "scene.h"

/**
 * Check whether the number of entry is correct and elements are not empty;
 * check whether the information is redefined (once defined, no matter succeed or not, cannot be redefined);
 * check whether the ratio is valid;
 * check whether the RGB is valid
 */
int	parse_ambient(char **array, t_scene *scene)
{
	if (scene->num_a)
		return (ft_putstr_fd("Error/nAmbient: more than 1 definition\n", 2), 1);
	scene->num_a = 1;
	if (!array || count_array_element(array) != 3 || !array[0] || !array[1] || !array[2])
		return (ft_putstr_fd("Error/nAmbient: Usage: A Ratio [r,g,b]\n", 2), 1);
	if (parse_doubles(array[1], scene) || parse_colors(array[2], scene))
		return (1);
	return (0);
}

