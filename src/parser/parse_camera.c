#include "scene.h"

// /**
//  * Check whether is valid coordinate;
//  * convert to coordinate and update position
//  */
// int	parse_position(char *s, t_scene *scene, t_vec3 *pos)
// {
// 	char	**arr;

// 	arr = ft_split(s, ',');
// 	if (!arr)
// 		return (error(FAIL_MEM_ALLOC), 1);
// 	if (count_array_element(arr) != 3 || !arr[0] || !arr[1] || !arr[2])
// 		return (clean_array(arr), 1);
// 	if (check_double(arr[0]) || check_double(arr[1]) || check_double(arr[2]))
// 		return (clean_array(arr), 1);
// 	(*pos).x = ft_atof(arr[0]);
// 	(*pos).y = ft_atof(arr[1]);
// 	(*pos).z = ft_atof(arr[2]);
// 	return (clean_array(arr), 0);
// }

// /**
//  * Check whether is valid coordinate;
//  * Check whether is zero vector;
//  * check whether is normalized, if not, convert to normalized vector
//  * convert to coordinate and update orientation
//  */
// int	parse_orient(char *s, t_scene *scene)
// {
// 	char	**arr;

// 	arr = ft_split(s, ',');
// 	if (!arr)
// 		return (error(FAIL_MEM_ALLOC), 1);
// 	if (count_array_element(arr) != 3 || !arr[0] || !arr[1] || !arr[2])
// 		return (clean_array(arr), 1);
// 	if (check_double(arr[0]) || check_double(arr[1]) || check_double(arr[2]))
// 		return (clean_array(arr), 1);
// 	scene->camera.orientation.x = ft_atof(arr[0]);
// 	scene->camera.orientation.y = ft_atof(arr[1]);
// 	scene->camera.orientation.z = ft_atof(arr[2]);
// 	if (scene->camera.orientation.x < EPSILON && scene->camera.orientation.y < EPSILON && scene->camera.orientation.z < EPSILON)
// 		return (clean_array(arr), 1);
// 	scene->camera.orientation = vec_normalize(scene->camera.orientation);
// 	return (clean_array(arr), 0);
// }

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
 * check whether the information is redefined (once defined, no matter succeed or not, cannot be redefined);
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
	if (!array || count_array_element(array) != 4 || !array[0] || !array[1] || !array[2] || !array[3])
		return (error(C_INVL_ARG), 1);
	if (parse_vector(array[1], &pos))
		return (error(C_INVL_POS), 1);
	if (parse_orientation(array[2], &orient))
		return (error(C_INVL_ORT), 1);
	if (parse_fov(array[3], &fov))
		return (error(C_INVL_FOV), 1);
	scene->camera.position = pos;
	scene->camera.orientation = orient;
	scene->camera.fov = fov;
	return (0);
}