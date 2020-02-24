#include "cub3D.h"

int		key_pressed(int key, t_var *var)
{
	if (key == A_KEY)
		var->key.a = 1;
	if (key == W_KEY)
		var->key.w = 1;
	if (key == S_KEY)
		var->key.s = 1;
	if (key == D_KEY)
		var->key.d = 1;
	if (key == LEFT_KEY)
		var->key.left = 1;
	if (key == RIGHT_KEY)
		var->key.right = 1;
	if (key == ESC_KEY)
		exit(0);
	return (1);
}

int		key_released(int key, t_var *var)
{
	if (key == A_KEY)
		var->key.a = 0;
	if (key == W_KEY)
		var->key.w = 0;
	if (key == S_KEY)
		var->key.s = 0;
	if (key == D_KEY)
		var->key.d = 0;
	if (key == LEFT_KEY)
		var->key.left = 0;
	if (key == RIGHT_KEY)
		var->key.right = 0;
	if (key == ESC_KEY)
		exit(0);
	return (1);
}

int		move_player(t_var *var)
{
	double	movement_speed;
	double	rotation_speed;

	movement_speed = 0.1;
	rotation_speed = 0.05;
	if (var->key.w == 1)
		vertical_movement(var, movement_speed, var->camera.dirX, var->camera.dirY);
	if (var->key.s == 1)
		vertical_movement(var, movement_speed, -var->camera.dirX, -var->camera.dirY);
	if (var->key.a == 1)
		horizontal_movement(var, movement_speed, -var->camera.planeX, -var->camera.planeY);
	if (var->key.d == 1)
		horizontal_movement(var, movement_speed, var->camera.planeX, var->camera.planeY);
	if (var->key.left)
		rotation(var, rotation_speed);
	if (var->key.right)
		rotation(var, -rotation_speed);
	render(var);
	mlx_put_image_to_window(var->mlx, var->win, var->img.id,
			0, 0);
	return (1);
}
