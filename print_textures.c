#include "cub3D.h"

char	*select_texture(t_var *var)
{
	if (var->ray.side == 0)
	{
		if (var->camera.dir_x < 0)
			return (var->file.we);
		return (var->file.ea);
	}
	else if (var->camera.dir_y < 0)
		return (var->file.no);
	else
		return (var->file.so);
}

int	main()
{
	void	*mlx;
	void	*win;
	void	*id;
	int		resolution_x = 700;
	int		resolution_y = 600;
	int		*addr;
	int		endian;
	int		bpp;
	int		size_line;
	int		width;
	int		height;

	if (!(mlx = mlx_init()))
		return (0);
	if (!(win = mlx_new_window(mlx, resolution_x, resolution_y, "cub3D")))
		return (0);
	void	*texture_image = mlx_xpm_file_to_image(mlx, "textures/wood.xpm", &width, &height);
	addr = (int*)mlx_get_data_addr(texture_image, &bpp, &size_line, &endian);
	mlx_put_image_to_window(mlx, win, texture_image, 0, 0);
	mlx_loop(mlx);
	return (1);
}
