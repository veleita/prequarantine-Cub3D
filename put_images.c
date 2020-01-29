#include <mlx.h>

int		create_trgb(int t, int r, int g, int b)
{
	return(t << 24 | r << 16 | g << 8 | b);
}

int main()
{
	void *mlx;
	void *win;
	void *img;
	int	 *img_addr;
	int	 bpp;
	int  line;
	int  endian;
	int x;
	int y;

	mlx = mlx_init();
	win = mlx_new_window(mlx, 1000, 1000, "porfa pinta cosas");
	img = mlx_new_image(mlx, 1000, 1000);
	img_addr = (int*)mlx_get_data_addr(img, &bpp, &line, &endian);
	
	y = 0;
	while (y < 500)
	{
		x = 0;
		while (x < 1000)
		{
			img_addr[y * 1000 + x] = create_trgb(0, 136, 212, 227);
			x++;
		}
		y++;
	}
	while (y < 1000)
	{
		x = 0;
		while (x < 1000)
		{
			img_addr[y * 1000 + x] = create_trgb(0, 115, 153, 99);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(mlx, win, img, 0, 0);
	mlx_put_image_to_window(mlx, win, img, 0, 0);
	mlx_loop(mlx);
	return (0);
}

