#include "cub3D.h"

void	vertical_movement(t_var *var, double movement_speed, double dirx,
		double diry)
{
	//printf("no %d\n", var->map[3][8]);
	//var->map.map[1][1] = 0;
	if (var->file.map[(int)(var->posx + dirx * 1)][(int)var->posy] == 0)
		var->posx += dirx * movement_speed;
	printf("\nmovement to X %d\n", var->file.map[(int)(var->posx + dirx * 1)][(int)(var->posy)]);
	if (var->file.map[(int)var->posx][(int)(var->posy + diry * 1)] == 0)
		var->posy += diry * movement_speed;
	printf("\nmovement to Y %d\n", var->file.map[(int)var->posx][(int)(var->posy + diry * 0.06)]);
}

void	horizontal_movement(t_var *var, double movement_speed, double planeX,
		double planeY)
{
	//printf("h");
	if (var->file.map[(int)(var->posx + planeX * 1)][(int)var->posy] == 0)
		var->posx += planeX * movement_speed;
	if (var->file.map[(int)var->posx][(int)(var->posy + planeY * 1)] == 0)
		var->posy += planeY * movement_speed;
	//printf("h");
}

void	rotation(t_var *var, double rotation_speed)
{
	double dirX_copy;
	double planeX_copy;

	dirX_copy = var->camera.dirX;
	var->camera.dirX = var->camera.dirX * cos(rotation_speed) - var->camera.dirY * sin(rotation_speed);
	var->camera.dirY = dirX_copy * sin(rotation_speed) + var->camera.dirY * cos(rotation_speed);
	planeX_copy = var->camera.planeX;
	var->camera.planeX = var->camera.planeX * cos(rotation_speed) - var->camera.planeY *
		sin(rotation_speed);
	var->camera.planeY = planeX_copy * sin(rotation_speed) + var->camera.planeY * cos(rotation_speed);
}
