#include "cub3D.h"

void	vertical_movement(t_var *var, double movement_speed, double dirx,
		double diry)
{
	printf("no %d\n", var->map.map[3][8]);
	//var->map.map[1][1] = 0;
	if (var->map.map[1][1] == 0)
		var->posx += dirx * movement_speed;
	if (var->map.map[1][1] == 0)
		var->posy += diry * movement_speed;
}

void	horizontal_movement(t_var *var, double movement_speed, double planeX,
		double planeY)
{
	var->posx += planeX * movement_speed;
	var->posy += planeY * movement_speed;
}

void	rotation(t_var *var, double rotation_speed)
{
	double dirX_copy;
	double planeX_copy;

	dirX_copy = var->dirX;
	var->dirX = var->dirX * cos(rotation_speed) - var->dirY * sin(rotation_speed);
	var->dirY = dirX_copy * sin(rotation_speed) + var->dirY * cos(rotation_speed);
	planeX_copy = var->planeX;
	var->planeX = var->planeX * cos(rotation_speed) - var->planeY *
		sin(rotation_speed);
	var->planeY = planeX_copy * sin(rotation_speed) + var->planeY * cos(rotation_speed);
}
