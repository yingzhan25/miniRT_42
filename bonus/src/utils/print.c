#include "minirt_bonus.h"

static void	print_object(const t_object *obj)
{
	if (obj->type == OBJ_PLANE)
	{
		printf("========Plane========\n");
		printf("x: %f\n", obj->u_data.plane.point.x);
		printf("y: %f\n", obj->u_data.plane.point.y);
		printf("z: %f\n", obj->u_data.plane.point.z);
		printf("nx: %f\n", obj->u_data.plane.normal.x);
		printf("ny: %f\n", obj->u_data.plane.normal.y);
		printf("nz: %f\n", obj->u_data.plane.normal.z);
	}
	else if (obj->type == OBJ_SPHERE)
	{
		printf("========Sphere========\n");
		printf("x: %f\n", obj->u_data.sphere.center.x);
		printf("y: %f\n", obj->u_data.sphere.center.y);
		printf("z: %f\n", obj->u_data.sphere.center.z);
		printf("diameter: %f\n", obj->u_data.sphere.diameter);
	}
	else if (obj->type == OBJ_CYLINDER)
	{
		printf("========Cylinder========\n");
		printf("x: %f\n", obj->u_data.cylinder.center.x);
		printf("y: %f\n", obj->u_data.cylinder.center.y);
		printf("z: %f\n", obj->u_data.cylinder.center.z);
		printf("nx: %f\n", obj->u_data.cylinder.axis.x);
		printf("ny: %f\n", obj->u_data.cylinder.axis.y);
		printf("nz: %f\n", obj->u_data.cylinder.axis.z);
		printf("diameter: %f\n", obj->u_data.cylinder.diameter);
		printf("height: %f\n", obj->u_data.cylinder.height);
	}
	printf("r: %d\n", obj->material.color.r);
	printf("g: %d\n", obj->material.color.g);
	printf("b: %d\n", obj->material.color.b);
}

void	print_scene(t_scene *scene)
{
	t_object	*obj;

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
	printf("========Light========\n");
	printf("x: %f\n", scene->light.position.x);
	printf("y: %f\n", scene->light.position.y);
	printf("z: %f\n", scene->light.position.z);
	printf("r: %d\n", scene->light.color.r);
	printf("g: %d\n", scene->light.color.g);
	printf("b: %d\n", scene->light.color.b);
	printf("brightness: %f\n", scene->light.brightness);
	obj = scene->objects;
	while (obj)
	{
		print_object(obj);
		obj = obj->next;
	}
}
