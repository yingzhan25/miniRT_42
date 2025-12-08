
#include "scene.h"
#include <fcntl.h>

/**
 * Check whether the scene file has a valid filename and ends with ".rt";
 * multiple entension(more than 1 dots) is forbidden
 */
int check_extension(char *s1, char *s2)
{
	int pos;
	int len;

	if (!s1 || !s1[0])
		return (1);
	pos = count_dot(s1);
	len = ft_strlen(s1);
	if (!pos || pos == -1 || pos == len - 1)
		return (1);
	if (len <= ft_strlen(s2) || ft_strcmp(s1 + len - ft_strlen(s2), s2))
		return (1);
	return (0);
}

/**
 * Check whether is empty line or new line;
 * Skip empty line and multiple spaces;
 * distribute data to corresponding parser function
 */
void	parse_line(char *line, t_scene *scene)
{
	char	**array;

	if (!line || !line[0] || line[0] == '\n')
		return ;
	array = ft_split(line, ' ');
	if (!array || !array[0])
		return ;
	if (!ft_strcmp(array[0], "A"))
		parse_ambient(array, scene);
	// else if (!ft_strcmp(array[0], "C"))
	// 	parse_camera(array, scene);
	// else if (!ft_strcmp(array[0], "L"))
	// 	parse_light(array, scene);
	//Parsing objects
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
	//Validate scene data
	return (scene);
}
