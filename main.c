#include "cub3D.h"

static int	init(t_var *var)
{
	if (!(var->mlx = mlx_init()))
		return (0);
	if (!(var->win = mlx_new_window(var->mlx, var->file.resolutionX,
					var->file.resolutionY, "cub3D")))
		return (0);
	//if (!(var->img.id = mlx_new_image(var->mlx, var->file.resolutionX,
	//				var->file.resolutionY)))
	//	return (0);
	//var->img.addr = (int*)mlx_get_data_addr(var->img.id, &var->img.bpp,
	//		&var->img.size_line, &var->img.endian);
	//ft_bzero(var->img.addr, var->file.resolutionX * var->file.resolutionY);
	//render(var);
	//mlx_put_image_to_window(var->mlx, var->win, var->img.id, 0, 0);
	return (1);
}

int	main(int argc, char **argv)
{
	t_var	*var;
	int		fd;
	(void)argc;

	if (!(var = (t_var*)malloc(sizeof(t_var))))
		return (-1);
	fd = open(argv[1], O_RDONLY);
	if (!read_map(argv[1], var, fd))
		return (-1);
	if (!(init(var)))
		return (-1);
	mlx_hook(var->win, 17, 0, &finish, var);
	mlx_hook(var->win, 2, 0, &key_pressed, var);
	mlx_hook(var->win, 3, 0, &key_released, var);
	//mlx_loop_hook(var->mlx, &move_player, var);
	mlx_loop(var->mlx);
	return (0);
}
