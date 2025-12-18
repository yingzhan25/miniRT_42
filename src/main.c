#include "scene.h"
#include "render.h"

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

int	main(int argc, char *argv[])
{
	t_scene		*scene;
	t_mlx_data	data;

	scene = parse_scene(argc, argv);
	if (!scene)
		return (1);
	print_scene(scene);
	data.mlx = mlx_init();
	data.window = mlx_new_window(data.mlx, WIN_WIDTH, WIN_HEIGHT, "./miniRT");
	data.image = mlx_new_image(data.mlx, WIN_WIDTH, WIN_HEIGHT);
	data.addr = mlx_get_data_addr(data.image, &data.bits_per_pixel, &data.line_length, &data.endian);
	data.scene = scene;
	setup_camera(&data.scene->camera);
	setup_viewport(&data.scene->camera);
	render_scene(&data);
	//Add mlx event hook
	mlx_loop(data.mlx);
	free_scene(scene);
	return (0);
}