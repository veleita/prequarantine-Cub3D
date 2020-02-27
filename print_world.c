#include "cub3D.h"

static int	rgb_to_hex(t_color color)
{
	int		ret;

	ret = color.r;
	ret = (ret << 8) | color.g;
	ret = (ret << 8) | color.b;
	return (ret);
}
/*

int		get_texture_pos(int texture_x, int texture_y, t_texture *texture)
{
	if (texture_x < 0 || texture_y < 0 || texture_x > texture->width ||
			texture_y > texture->height)
		return (0);
	return (texture->image[(int)(texture_y * texture->width + texture_x)]);
}*/

static int		*create_texture(t_var *var)
{
	var->texture.id = mlx_xpm_file_to_image(var->mlx, var->file.we,
			&var->texture.width, &var->texture.height);
	var->texture.addr = (int*)mlx_get_data_addr(var->texture.id, 
			&var->texture.bpp, &var->texture.size_line, &var->texture.endian);
	return (var->texture.addr);
}

void	print_column(t_var *var, int x, int texture_x)
{
	int		y;
	double	texture_y;
	double	step;
	double	texture_pos;

	var->texture.addr = create_texture(var);
	if ((var->ray.side == 0 && var->ray.dirx > 0) ||
		(var->ray.side == 1 && var->ray.diry < 0))
		texture_x = var->texture.width - texture_x - 1;
	y = -1;
	while (y < var->ray.drawstart)
		var->img.addr[++y * var->file.resolution_x + x] = 
			rgb_to_hex(var->file.floor_rgb);
	step = 1.0 * var->texture.height / var->ray.lineheight;
	texture_pos = (var->ray.drawstart - var->file.resolution_y / 2 +
			var->ray.lineheight / 2) * step;
	while (y < var->ray.drawend - 1)
	{
		texture_y = (int)texture_pos & (var->texture.height - 1);
		texture_pos += step;
		var->img.addr[(y++ * var->file.resolution_x) + x] = 
			var->texture.addr[(int)(texture_y * var->texture.width + texture_x)];
			//get_texture_pos(texture_x, texture_y, &var->texture);
	}
	mlx_destroy_image(var->mlx, var->texture.id);
		/*if (var->ray.side)
			var->img.addr[++y * var->file.resolutionX + x] = 0x222c2e/2;
		var->img.addr[++y * var->file.resolutionX + x] = 0x222cff;*/
	while (y < (var->file.resolution_y - 1))
		var->img.addr[++y * var->file.resolution_x + x] = 0xd7eff5;
}
