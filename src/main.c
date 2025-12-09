#include "scene.h"
#include "stdio.h"

int	main(int argc, char *argv[])
{
	t_scene	*scene;

	scene = parse_scene(argc, argv);
	if (!scene)
		return (1);
	printf("ratio: %f\n", scene->ambient.ratio);
	printf("ratio: %f\n", scene->ambient.color.x);
	printf("ratio: %f\n", scene->ambient.color.y);
	printf("ratio: %f\n", scene->ambient.color.z);
	free(scene);
	return (0);
}