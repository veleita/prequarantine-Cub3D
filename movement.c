#include "cub3D.h"

void	vertical_movement(t_var *var, double movement_speed, double dirx,
		double diry)
{
	if (var->file.map[(int)(var->pos_x + dirx * 1)][(int)var->pos_y] == 0)
		var->pos_x += dirx * movement_speed;
	if (var->file.map[(int)var->pos_x][(int)(var->pos_y + diry * 1)] == 0)
		var->pos_y += diry * movement_speed;
}

void	horizontal_movement(t_var *var, double movement_speed, double plane_x,
		double planeY)
{
	//printf("h");
	if (var->file.map[(int)(var->pos_x + plane_x * 1)][(int)var->pos_y] == 0)
		var->pos_x += plane_x * movement_speed;
	if (var->file.map[(int)var->pos_x][(int)(var->pos_y + planeY * 1)] == 0)
		var->pos_y += planeY * movement_speed;
	//printf("h");
}

void	rotation(t_var *var, double rotation_speed)
{
	double dir_x_copy;
	double plane_x_copy;

	dir_x_copy = var->camera.dir_x;
	var->camera.dir_x = var->camera.dir_x * cos(rotation_speed) -
		var->camera.dir_y * sin(rotation_speed);
	var->camera.dir_y = dir_x_copy * sin(rotation_speed) + var->camera.dir_y *
		cos(rotation_speed);
	plane_x_copy = var->camera.plane_x;
	var->camera.plane_x = var->camera.plane_x * cos(rotation_speed) - 
		var->camera.plane_y * sin(rotation_speed);
	var->camera.plane_y = plane_x_copy * sin(rotation_speed) + 
		var->camera.plane_y * cos(rotation_speed);
}
