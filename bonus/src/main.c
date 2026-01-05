#include "minirt_bonus.h"

int	main(int argc, char *argv[])
{
	t_scene		*scene;
	t_mlx_data	*data;

	scene = parse_scene(argc, argv);
	if (!scene)
		return (1);
	print_scene(scene);
	data = malloc(sizeof(t_mlx_data));
	if (!data)
		return (error(FAIL_MEM_ALLOC), 1);
	mlx_data_init(data, scene);
	setup_camera(&data->scene->camera);
	setup_viewport(&data->scene->camera);
	render_scene(data);
	handle_events(data);
	return (0);
}
