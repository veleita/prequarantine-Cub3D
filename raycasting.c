#include "cub3D.h"

void	get_side_dist(int x, t_var *var)
{
	var->ray.cameraX = 2 * x / (double)var->screenWidth - 1;

	var->ray.raydirx = var->dirX + var->planeX * var->ray.cameraX;
	var->ray.raydiry = var->dirY + var->planeY * var->ray.cameraX;

	var->ray.mapx = (int)var->posx;
	var->ray.mapy = (int)var->posy;

	var->ray.deltadistx = sqrt(1 + (var->ray.raydiry * var->ray.raydiry) /
			(var->ray.raydirx * var->ray.raydirx));
	var->ray.deltadisty = sqrt(1 + (var->ray.raydirx * var->ray.raydirx) /
			(var->ray.raydiry * var->ray.raydiry));
	var->ray.stepx = (var->ray.raydirx < 0) ? -1 : 1;
	if (var->ray.raydirx < 0)
		var->ray.sidedistx = (var->posx - var->ray.mapx) *
			var->ray.deltadistx;
	else
		var->ray.sidedistx = (var->ray.mapx + 1.0 - var->posx) *
			var->ray.deltadistx;
	var->ray.stepy = (var->ray.raydiry < 0) ? -1 : 1;
	if (var->ray.raydiry < 0)
		var->ray.sidedisty = (var->posy - var->ray.mapy) *
			var->ray.deltadisty;
	else
		var->ray.sidedisty = (var->ray.mapy + 1.0 - var->posy) *
			var->ray.deltadisty;
}

void	get_hit(t_var *var, int map[16][29])
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
		if (map[var->ray.mapx][var->ray.mapy] > 0)
			var->ray.hit = 1;
	}
}

void		get_wall(t_var *var)
{
	if (var->ray.side == 0)
		var->ray.perpWallDist = (var->ray.mapx - var->posx +
				(1 - var->ray.stepx) / 2.) / var->ray.raydirx;
	else
		var->ray.perpWallDist = (var->ray.mapy - var->posy +
				(1 - var->ray.stepy) / 2.) / var->ray.raydiry;
	var->ray.perpWallDist *= var->ray.perpWallDist < 0 ? -1 : 1;
	var->ray.lineHeight = (int)(var->screenHeight /
			var->ray.perpWallDist);
	var->ray.drawStart = var->screenHeight / 2 - var->ray.lineHeight / 2;
	var->ray.drawStart = (var->ray.drawStart < 0) ?
		0 : var->ray.drawStart;
	var->ray.drawEnd = var->screenHeight / 2 + var->ray.lineHeight / 2;
	var->ray.drawEnd = (var->ray.drawEnd >= var->screenHeight) ?
		var->screenHeight - 1 : var->ray.drawEnd;
}
