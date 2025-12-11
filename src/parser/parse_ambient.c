#include "scene.h"

/**
 * Check whether the number of entry is correct and elements are not empty;
 * check whether the information is redefined (once defined, no matter succeed or not, cannot be redefined);
 * check whether the ratio is valid;
 * check whether the RGB is valid
 */
int	parse_ambient(char **array, t_scene *scene, char *name)
{
	if (scene->num_a)
		return (error(name, "duplicate", "more than 1 definition\n"), 1);
	scene->num_a = 1;
	if (!array || count_array_element(array) != 3 || !array[0] || !array[1] || !array[2])
		return (error(name, "Usage", "A ratio [r,g,b]\n"), 1);
	return (parse_ratio(array[1], scene, name, "ratio") || parse_colors(array[2], scene, name, "colors"));
}

// int	parse_camera(char **array, t_scene *scene, char *name)
// {
// 	if (scene->num_c)
// 		return (error(name, "duplicate", "more than 1 definition\n"), 1);
// 	scene->num_c = 1;
// 	if (!array || count_array_element(array) != 4 || !array[0] || !array[1] || !array[2] || !array[3])
// 		return (error("name", "Usage", "C [x,y,z] [nx,ny,nz] fov\n"), 1);
// 	return (parse_tuples(array[1], scene, name, "position"));
// }
