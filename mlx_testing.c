#include <mlx.h>
#include <stdio.h>

int main()
{
	void *mlx;

	mlx = mlx_init();
	mlx_new_window(mlx, 500, 500, "Hello world!");
	mlx_loop(mlx);
	return (0);
}
