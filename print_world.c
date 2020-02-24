#include "cub3D.h"

void	print_column(t_var *var, int x)
{
	int y;

	y = -1;
	while (y < var->ray.drawStart)
		var->img.addr[++y * var->file.resolutionX + x] = 0x94d6a6;
	while (y < var->ray.drawEnd - 1)
	{
		if (var->ray.side)
			var->img.addr[++y * var->file.resolutionX + x] = 0x222c2e/2;
		var->img.addr[++y * var->file.resolutionX + x] = 0x222cff;
	}
	while (y < (var->file.resolutionY - 1))
		var->img.addr[++y * var->file.resolutionX + x] = 0xd7eff5;
}
