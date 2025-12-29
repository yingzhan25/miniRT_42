#include "minirt.h"

/**
 * Check whether is valid double;
 * Check whether is in the valid range;
 * convert to double and update fov
 */
int	parse_fov(char *s, double *fov)
{
	if (check_double(s))
		return (1);
	*fov = ft_atof(s);
	if (*fov < FOV_MIN || *fov > FOV_MAX)
		return (1);
	return (0);
}

/**
 * Check whether the number of entry is correct and elements are not empty;
 * check whether the information is redefined
 * (once defined, no matter succeed or not, cannot be redefined);
 * check whether the position is valid;
 * check whether the orientation is valid
 * check whether the fov is valid
 */
int	parse_camera(char **array, t_scene *scene)
{
	t_vec3	pos;
	t_vec3	orient;
	double	fov;

	if (scene->num_c)
		return (error(C_MULTIPLE_DEF), 1);
	scene->num_c = 1;
	if (!array || C_A_E(array) != 4 || \
		!array[0] || !array[1] || !array[2] || !array[3])
		return (error(C_INVL_ARG), 1);
	if (P_VEC(array[1], &pos))
		return (error(C_INVL_POS), 1);
	if (P_ORI(array[2], &orient))
		return (error(C_INVL_ORT), 1);
	if (P_FOV(array[3], &fov))
		return (error(C_INVL_FOV), 1);
	scene->camera.position = pos;
	scene->camera.orientation = orient;
	scene->camera.fov = fov;
	return (0);
}
