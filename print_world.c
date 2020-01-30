#include "cub3D.h"

void	print_column(t_var *var, int x)
{
	int y;

	y = -1;
	while (y < var->ray.drawStart)
		var->img.addr[++y * var->screenWidth + x] = 0x990000;
	while (y < var->ray.drawEnd - 1)
		var->img.addr[++y * var->screenWidth + x] = 0x009900;
	while (y < (var->screenHeight - 1))
		var->img.addr[++y * var->screenWidth + x] = 0x000099;
}
