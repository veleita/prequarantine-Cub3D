#include <mlx.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>
/*
 * ---------------------------------STRUCTS------------------------------------
 */
typedef struct  s_data 
{
    void        *img;
    char        *addr;
    int         bits_per_pixel;
    int         line_length;
    int         endian;
}               t_data;

typedef struct s_mlx
{
	void		*mlx;
	void		*win;
}				t_mlx;

typedef struct	s_color
{
	int			t;
	int			r;
	int			g;
	int			b;
}				t_color;
/*
 * -------------------------------COLOR MANAGEMENT-----------------------------
 */
int		create_trgb(int t, int r, int g, int b)
{
	return(b << 24 | g << 16 | r << 8 | t);
}
/*
 * ------------------------------IMAGE MANAGEMENT------------------------------
 */
void            my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}
/*
 * -----------------------------------EVENTS-----------------------------------
 */
int				close_window(int keycode, t_mlx *mlx)
{
	if (keycode == 53)
		mlx_destroy_window(mlx->mlx, mlx->win);
	return (1);
}

int				print_key(int keycode, t_mlx *mlx)
{
	(void)mlx;
	printf("%d\n", keycode);
	return (1);
}
/*
 *---------------------------------------MAIN----------------------------------
 */
int             main(void)
{
    t_mlx	mlx;
	//t_data  img;
	//int		y;
	//int		x;

    mlx.mlx = mlx_init();
    mlx.win = mlx_new_window(mlx.mlx, 500, 500, "Hello world!");
    //img.img = mlx_new_image(mlx.mlx, 500, 500);
    //img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
	//							 &img.endian);
	mlx_key_hook(mlx.win, close_window, &mlx);
	//mlx_key_hook(mlx.win, print_key, &mlx);

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
    //mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx.mlx);
	return (0);
}
