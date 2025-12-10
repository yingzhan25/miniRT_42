
#include "scene.h"
#include <fcntl.h>


/**
 * Check whether is empty line or new line;
 * skip empty line and multiple spaces;
 * distribute data to corresponding parser function;
 * once any parser fails, record FAIL flag and keep reading until GNL return NULL(avoid memory leak);
 * clean up memory before return
 */
void	parse_line(char *line, t_scene *scene)
{
	char	**array;

	if (!line || !line[0] || line[0] == '\n')
		return ;
	array = ft_split(line, ' ');
	if (!array || !array[0])
		return ;
	//if any parser fails, should clean up array, line and the whole struct before return
	if (!ft_strcmp(array[0], "A"))
	{
		if (parse_ambient(array, scene))
			scene->fail_to_parse = 1;
	}
	// else if (!ft_strcmp(array[0], "C"))
	// 	parse_camera(array, scene);
	// else if (!ft_strcmp(array[0], "L"))
	// 	parse_light(array, scene);
	//Parsing objects
	else
	{
		ft_putstr_fd("Error/nUndefined element/object type\n", 2);
		scene->fail_to_parse = 1;
	}
	clean_array(array);
}

/**
 * Check whether the argument number is correct;
 * check whether the extension is correct;
 * check whether the file can be opened;
 * allocate memory and initialize the struct;
 * (on heap to have more memory space for multiple objects)
 * read scene data by GNL and write to struct;
 * validate scene data in struct
 */
t_scene *parse_scene(int ac, char *av[])
{
	int		fd;
	char	*line;
	t_scene *scene;

	if (ac != 2 || check_extension(av[1], ".rt"))
		return (ft_putstr_fd("Error\nUsage: ./minirt <scene.rt>\n", 2), NULL);
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		return (ft_putstr_fd("Error\nCannot open file\n", 2), NULL);
	scene = malloc(sizeof(t_scene));
	if (!scene)
		return (ft_putstr_fd("Error\nMemory allocation failed\n", 2), close(fd), NULL);
	ft_memset(scene, 0, sizeof(t_scene));
	line = get_next_line(fd);
	while (line)
	{
		parse_line(line, scene);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
//	if (scene->fail_to_parse || scene->num_a != 1 || scene->num_c != 1 || scene->num_l != 1)
//		return (free(scene), NULL);
	return (scene);
}
