
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
	char	*line_trim;

	if (!line || !line[0] || line[0] == '\n')
		return ;
	line_trim = ft_strtrim(line, "\n");
	array = ft_split(line_trim, ' ');
	free(line_trim);
	if (!array || !array[0])
		return ;
	//if any parser fails, should clean up array, line and the whole struct before return
	if (!ft_strcmp(array[0], "A"))
		scene->fail_to_parse = parse_ambient(array, scene);
	else if (!ft_strcmp(array[0], "C"))
		scene->fail_to_parse = parse_camera(array, scene);
	else if (!ft_strcmp(array[0], "L"))
		parse_light(array, scene);
	else if (!is_object(array[0]))
		scene->fail_to_parse = parse_objects(array, scene);
	else
	{
		error(UNDEFINE_OBJS);
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
		return (error(INVALID_ARG_NUM), NULL);
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		return (error(FAIL_OPEN_FILE), NULL);
	scene = malloc(sizeof(t_scene));
	if (!scene)
		return (error(FAIL_MEM_ALLOC), close(fd), NULL);
	ft_memset(scene, 0, sizeof(t_scene));
	line = get_next_line(fd);
	while (line)
	{
//		printf("line: %s", line);
		parse_line(line, scene);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if (scene->fail_to_parse || scene->num_a != 1 || scene->num_c != 1 || scene->num_l != 1)
		return (free(scene), NULL);
	return (scene);
}
