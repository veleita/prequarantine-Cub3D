#include <mlx.h>
#include <stdio.h>
#include <math.h>

typedef struct  s_data {
    void        *img;
    char        *addr;
    int         bits_per_pixel;
    int         line_length;
    int         endian;
}               t_data;

void            my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

int             main(void)
{
    void    *mlx;
    void    *mlx_win;
	t_data  img;
//	int		y;
//	int		x;

    mlx = mlx_init();
    mlx_win = mlx_new_window(mlx, 500, 500, "Hello world!");
    img.img = mlx_new_image(mlx, 500, 500);
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								 &img.endian);
/*
 *---------------------------PRINT A SQUARE------------------------------------
 * 
 *	while (250 - x == 250 - y)
 *		my_mlx_pixel_put(&img, x, y, 0x00FF0000);
 *	while (x++ < 250)
 *		my_mlx_pixel_put(&img, x, y, 0x00FF0000);
 *	while (y-- > 100)
 *		my_mlx_pixel_put(&img, x, y, 0x00FF0000);
 *	while (x-- > 100)
 *		my_mlx_pixel_put(&img, x, y, 0x00FF0000);
 */
/*
 * --------------------------PRINT A CIRCLE------------------------------------
 *	while (x++ < 200)
 *	{
 *		my_mlx_pixel_put(&img, x, y, 0x00FF0000);
 *		y = sqrt(x*x + 2*x + 8) - 2;
 *	}
 */
    mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
	return (0);
}
