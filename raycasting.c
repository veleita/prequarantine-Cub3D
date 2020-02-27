#include "cub3D.h"

void	get_side_dist(int x, t_var *var)
{
	var->ray.camera_x = 2 * x / (double)var->file.resolution_x - 1;

	var->ray.dirx = var->camera.dir_x + var->camera.plane_x *
		var->ray.camera_x;
	var->ray.diry = var->camera.dir_y + var->camera.plane_y *
		var->ray.camera_x;

	var->ray.mapx = (int)var->pos_x;
	var->ray.mapy = (int)var->pos_y;

	var->ray.deltadistx = sqrt(1 + (var->ray.diry * var->ray.diry) /
			(var->ray.dirx * var->ray.dirx));
	var->ray.deltadisty = sqrt(1 + (var->ray.dirx * var->ray.dirx) /
			(var->ray.diry * var->ray.diry));
	var->ray.stepx = (var->ray.dirx < 0) ? -1 : 1;
	if (var->ray.dirx < 0)
		var->ray.sidedistx = (var->pos_x - var->ray.mapx) *
			var->ray.deltadistx;
	else
		var->ray.sidedistx = (var->ray.mapx + 1.0 - var->pos_x) *
			var->ray.deltadistx;
	var->ray.stepy = (var->ray.diry < 0) ? -1 : 1;
	if (var->ray.diry < 0)
		var->ray.sidedisty = (var->pos_y - var->ray.mapy) *
			var->ray.deltadisty;
	else
		var->ray.sidedisty = (var->ray.mapy + 1.0 - var->pos_y) *
			var->ray.deltadisty;
}

void	get_hit(t_var *var)
{
	var->ray.hit = 0;
	while (var->ray.hit == 0)
	{
		if (var->ray.sidedistx < var->ray.sidedisty)
		{
			var->ray.sidedistx += var->ray.deltadistx;
			var->ray.mapx += var->ray.stepx;
			var->ray.side = 0;
		}
		else
		{
			var->ray.sidedisty += var->ray.deltadisty;
			var->ray.mapy += var->ray.stepy;
			var->ray.side = 1;
		}
		if (var->file.map[var->ray.mapx][var->ray.mapy] > 0)
			var->ray.hit = 1;
	}
}

void	get_wall_hit(t_var *var)
{
	if (var->ray.side == 1)
	{
		var->ray.wallhit_x = var->pos_x + ((var->ray.mapy - var->pos_y
		+ (1 - var->ray.stepy) / 2) / var->ray.diry) * var->ray.dirx;
		//var->texture.path = var->ray.diry < 0 ? var->file.no : var->file.ea;
	}
	else
	{
		var->ray.wallhit_x = var->pos_y + ((var->ray.mapx - var->pos_x
		+ (1 - var->ray.stepx) / 2) / var->ray.dirx) * var->ray.diry;
		//var->texture.path = var->ray.dirx < 0 ? var->file.so : var->file.we;
	}
	var->ray.wallhit_x -= floor(var->ray.wallhit_x);
}

void		get_wall(t_var *var)
{
	if (var->ray.side == 0)
		var->ray.perpWallDist = (var->ray.mapx - var->pos_x +
				(1 - var->ray.stepx) / 2.) / var->ray.dirx;
	else
		var->ray.perpWallDist = (var->ray.mapy - var->pos_y +
				(1 - var->ray.stepy) / 2.) / var->ray.diry;
	var->ray.perpWallDist *= var->ray.perpWallDist < 0 ? -1 : 1;
	var->ray.lineheight = (int)(var->file.resolution_y /
			var->ray.perpWallDist);
	var->ray.drawstart = var->file.resolution_y / 2 - var->ray.lineheight / 2;
	var->ray.drawstart = (var->ray.drawstart < 0) ?
		0 : var->ray.drawstart;
	var->ray.drawend = var->file.resolution_y / 2 + var->ray.lineheight / 2;
	var->ray.drawend = (var->ray.drawend >= var->file.resolution_y) ?
		var->file.resolution_y - 1 : var->ray.drawend;
}
