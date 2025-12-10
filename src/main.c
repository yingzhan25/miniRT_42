#include "scene.h"

int	main(int argc, char *argv[])
{
	t_scene	*scene;

	scene = parse_scene(argc, argv);
	if (!scene)
		return (1);
	printf("========Test for Ambient========\n");
	printf("ratio: %f\n", scene->ambient.ratio);
	printf("r: %d\n", scene->ambient.color.r);
	printf("g: %d\n", scene->ambient.color.g);
	printf("b: %d\n", scene->ambient.color.b);
	free(scene);
	return (0);
}