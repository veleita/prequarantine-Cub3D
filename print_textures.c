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
	if (!(id = mlx_new_image(mlx, resolution_x, resolution_y)))
		return (0);
	addr = (int*)mlx_get_data_addr(id, &bpp, &size_line, &endian);
	ft_bzero(addr, resolution_x * resolution_y);
	int	*texture_image = mlx_xpm_file_to_image(mlx, "textures/eagle.xpm",
			&width, &height);
	mlx_put_image_to_window(mlx, win, id, 0, 0);
	mlx_loop(mlx);
	return (1);
}
