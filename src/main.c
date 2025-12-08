#include "scene.h"

int	main(int argc, char *argv[])
{
	t_scene	*scene;

	scene = parse_scene(argc, argv);
	if (!scene)
		return (1);
	return (0);
}