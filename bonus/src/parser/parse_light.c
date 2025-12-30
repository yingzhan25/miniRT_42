#include "minirt_bonus.h"

/**
 * Check whether the number of entry is correct and elements are not empty;
 * check whether the information is redefined
 * (once defined, no matter succeed or not, cannot be redefined);
 * check whether the position is valid;
 * check whether the color is valid
 * check whether the brightness is valid
 */
int	parse_light(char **array, t_scene *scene)
{
	t_vec3	pos;
	double	bright;
	t_color	color;

	// if (scene->num_l)
	// 	return (error(L_MULTIPLE_DEF), 1);
	scene->num_l = 1;
	if (!array || C_A_E(array) != 4 || \
		!array[0] || !array[1] || !array[2] || !array[3])
		return (error(L_INVL_ARG), 1);
	if (P_VEC(array[1], &pos))
		return (error(L_INVL_POS), 1);
	if (P_RAT(array[2], &bright))
		return (error(L_INVL_BRIGHT), 1);
	if (P_COL(array[3], &color))
		return (error(L_INVL_COLOR), 1);
	scene->light.position = pos;
	scene->light.brightness = bright;
	scene->light.color = color;
	return (0);
}
