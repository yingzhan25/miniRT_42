#include "scene.h"

int	parse_position(char *s, t_scene *scene)
{
	char	**arr;

	arr = ft_split(s, ',');
	if (!arr)
		return (error(FAIL_MEM_ALLOC), 1);
	if (count_array_element(arr) != 3 || !arr[0] || !arr[1] || !arr[2])
		return (error(C_INVL_POS), clean_array(arr), 1);
	if (check_double(arr[0]) || check_double(arr[1]) || check_double(arr[2]))
		return (error(C_INVL_POS), clean_array(arr), 1);
	scene->camera.position.x = ft_atof(arr[0]);
	scene->camera.position.y = ft_atof(arr[1]);
	scene->camera.position.z = ft_atof(arr[2]);
	return (clean_array(arr), 0);
}

int	parse_orient(char *s, t_scene *scene)
{
	char	**arr;

	arr = ft_split(s, ',');
	if (!arr)
		return (error(FAIL_MEM_ALLOC), 1);
	if (count_array_element(arr) != 3 || !arr[0] || !arr[1] || !arr[2])
		return (error(C_INVL_ORT), clean_array(arr), 1);
	if (check_double(arr[0]) || check_double(arr[1]) || check_double(arr[2]))
		return (error(C_INVL_ORT), clean_array(arr), 1);
	scene->camera.orientation.x = ft_atof(arr[0]);
	scene->camera.orientation.y = ft_atof(arr[1]);
	scene->camera.orientation.z = ft_atof(arr[2]);
	if (scene->camera.orientation.x < EPSILON && scene->camera.orientation.y < EPSILON && scene->camera.orientation.z < EPSILON)
		return (error(C_EXCD_ORT), clean_array(arr), 1);
	return (clean_array(arr), 0);
}

int	parse_fov(char *s, t_scene *scene)
{
	if (check_double(s))
		return (error(C_INVL_FOV), 1);
	scene->camera.fov = ft_atof(s);
	if (scene->camera.fov < FOV_MIN || scene->camera.fov > FOV_MAX)
		return (error(C_EXCD_FOV), 1);
	return (0);
}

int	parse_camera(char **array, t_scene *scene)
{
	if (scene->num_c)
		return (error(C_MULTIPLE_DEF), 1);
	scene->num_c = 1;
	if (!array || count_array_element(array) != 4 || !array[0] || !array[1] || !array[2] || !array[3])
		return (error(INVALID_C_ARG), 1);
	return (parse_position(array[1], scene) || parse_orient(array[2], scene) || parse_fov(array[3], scene));
}