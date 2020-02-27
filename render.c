#include "cub3D.h"
/*
char	*select_texture(t_var *var)
{
	if (var->ray.side == 0)
	{
		if (var->ray.dirx < 0)
			return (var->file.we);
		return (var->file.ea);
	}
	else if (var->ray.diry < 0)
		return (var->file.no);
	else
		return (var->file.so);
}
*/
/*
static int		*create_texture(t_var *var, char *path)
{
	var->texture.id = mlx_xpm_file_to_image(var->mlx, path,
			&var->texture.width, &var->texture.height);
	var->texture.addr = (int*)mlx_get_data_addr(var->texture.id, 
			&var->texture.bpp, &var->texture.size_line, &var->texture.endian);
	return (var->texture.addr);
}*/

void	render(t_var *var)
{
	int x;
	int	old_side;
/*
	int map[16][29]=
	{
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,0,0,0,0,0,0,0,2,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
		{1,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,1,1,0,0,0,0,0,1,1,1,0,0,0,0,0,0,2,0,0,0,0,0,1,0,0,0,1},
		{1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,1},
		{1,0,1,1,0,0,0,0,0,1,1,1,0,2,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,1,1,1,0,1,1,1,1,0,0,0,1},
		{1,1,1,1,0,1,1,1,1,1,1,1,1,1,0,1,1,1,0,0,0,0,0,0,1,0,0,0,1},
		{1,1,1,1,0,1,1,1,1,1,1,1,1,1,0,1,1,1,0,1,0,1,0,0,1,0,0,0,1},
		{1,1,0,0,0,0,0,0,1,1,0,1,0,1,0,1,1,1,0,0,0,0,2,0,1,0,0,0,1},
		{1,0,0,2,2,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,1,0,1,0,0,1,0,0,0,1},
		{1,1,0,0,0,0,0,0,1,1,0,1,0,1,0,1,1,1,1,1,0,1,1,1,1,0,0,0,1},
		{1,1,1,1,0,1,1,1,1,1,1,1,0,1,0,1,1,1,1,1,0,1,1,1,1,0,0,0,1}
	};*/
	x = -1;
	//var->texture.addr = create_texture(var, var->file.no);
	while (++x < var->file.resolution_x)
	{
		get_side_dist(x, var);
		old_side = var->ray.side;
		get_hit(var);
		get_wall(var);
		get_wall_hit(var);
		//if (old_side != var->ray.side)
		//	var->texture.path =  var->file.ea;
		//else
		//	var->texture.path = var->file.so;
		print_column(var, x, ((int)(var->ray.wallhit_x * (double)(var->texture.width))));
	}
}
