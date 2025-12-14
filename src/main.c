#include "scene.h"

static void	print_object(const t_object *obj)
{
	if (obj->type == OBJ_PLANE)
	{
		printf("========Plane========\n");
		printf("x: %f\n", obj->data.plane.point.x);
		printf("y: %f\n", obj->data.plane.point.y);
		printf("z: %f\n", obj->data.plane.point.z);
		printf("nx: %f\n", obj->data.plane.normal.x);
		printf("ny: %f\n", obj->data.plane.normal.y);
		printf("nz: %f\n", obj->data.plane.normal.z);
	}
	else if (obj->type == OBJ_SPHERE)
	{
		printf("========Sphere========\n");
		printf("x: %f\n", obj->data.sphere.center.x);
		printf("y: %f\n", obj->data.sphere.center.y);
		printf("z: %f\n", obj->data.sphere.center.z);
		printf("diameter: %f\n", obj->data.sphere.diameter);
	}
	else if (obj->type == OBJ_CYLINDER)
	{
		printf("========Cylinder========\n");
		printf("x: %f\n", obj->data.cylinder.center.x);
		printf("y: %f\n", obj->data.cylinder.center.y);
		printf("z: %f\n", obj->data.cylinder.center.z);
		printf("nx: %f\n", obj->data.cylinder.axis.x);
		printf("ny: %f\n", obj->data.cylinder.axis.y);
		printf("nz: %f\n", obj->data.cylinder.axis.z);
		printf("diameter: %f\n", obj->data.cylinder.diameter);
		printf("height: %f\n", obj->data.cylinder.height);
	}
	printf("r: %d\n", obj->color.r);
	printf("g: %d\n", obj->color.g);
	printf("b: %d\n", obj->color.b);
}

int	main(int argc, char *argv[])
{
	t_scene		*scene;
	t_object	*obj;

	scene = parse_scene(argc, argv);
	if (!scene)
		return (1);
	printf("========Ambient========\n");
	printf("ratio: %f\n", scene->ambient.ratio);
	printf("r: %d\n", scene->ambient.color.r);
	printf("g: %d\n", scene->ambient.color.g);
	printf("b: %d\n", scene->ambient.color.b);
	printf("========Camera========\n");
	printf("x: %f\n", scene->camera.position.x);
	printf("y: %f\n", scene->camera.position.y);
	printf("z: %f\n", scene->camera.position.z);
	printf("nx: %f\n", scene->camera.orientation.x);
	printf("ny: %f\n", scene->camera.orientation.y);
	printf("nz: %f\n", scene->camera.orientation.z);
	printf("fov: %f\n", scene->camera.fov);
	obj = scene->objects;
	while (obj)
	{
		print_object(obj);
		obj = obj->next;
	}
	free(scene);
	return (0);
}