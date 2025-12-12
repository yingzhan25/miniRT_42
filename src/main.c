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
	printf("========Test for Camera========\n");
	printf("x: %f\n", scene->camera.position.x);
	printf("y: %f\n", scene->camera.position.y);
	printf("z: %f\n", scene->camera.position.z);
	printf("nx: %f\n", scene->camera.orientation.x);
	printf("ny: %f\n", scene->camera.orientation.y);
	printf("nz: %f\n", scene->camera.orientation.z);
	printf("fov: %f\n", scene->camera.fov);
	printf("========Test for Plane========\n");
	printf("x: %f\n", scene->objects->data.plane.point.x);
	printf("y: %f\n", scene->objects->data.plane.point.y);
	printf("z: %f\n", scene->objects->data.plane.point.z);
	printf("nx: %f\n", scene->objects->data.plane.normal.x);
	printf("ny: %f\n", scene->objects->data.plane.normal.y);
	printf("nz: %f\n", scene->objects->data.plane.normal.z);
	printf("r: %d\n", scene->objects->color.r);
	printf("g: %d\n", scene->objects->color.g);
	printf("b: %d\n", scene->objects->color.b);
	free(scene);
	return (0);
}