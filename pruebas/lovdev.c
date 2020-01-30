#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <mlx.h>

#define mapWidth 24
#define mapHeight 24
#define screenWidth 640
#define screenHeight 480
#define wallHeight 400

typedef struct s_id
{
	void		*mlx;
	void		*win;
	int		*img_addr;
	void		*img;
	int			bpp;
	int			line;
	int			endian;
}				t_id;

int worldMap[mapWidth][mapHeight]=
{
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

int		create_trgb(int t, int r, int g, int b)
{
	return(t << 24 | r << 16 | g << 8 | b);
}

/*void            my_mlx_pixel_put(t_id *var, int x, int y, int color)
{
    char    *dst;

    dst = var->img_addr + (y * screenWidth + x * (var->bpp / 8));
    *(unsigned int*)dst = color;
}*/

void	draw_background(t_id *val)
{
	int  line;
	int  endian;
	int x;
	int y;

	printf("entra");
	val->mlx = mlx_init();
	val->win = mlx_new_window(val->mlx, 1000, 1000, "porfa pinta cosas");
	val->img = mlx_new_image(val->mlx, 1000, 1000);
	val->img_addr = (int*)mlx_get_data_addr(val->img, &val->bpp, &line, &endian);

	y = 0;
	while (y < 500)
	{
		x = 0;
		while (x < 1000)
		{
			val->img_addr[y * 1000 + x] = create_trgb(0, 136, 212, 227);
			x++;
		}
		y++;
	}
	while (y < 1000)
	{
		x = 0;
		while (x < 1000)
		{
			val->img_addr[y * 1000 + x] = create_trgb(0, 115, 153, 99);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(val->mlx, val->win, val->img, 0, 0);
	mlx_destroy_image(val->mlx, val->img);
	mlx_loop(val->mlx);
}

void	draw_column(int x, int drawStart, int drawEnd, t_id *val)
{
	//int endian = 1;
	//int w = screenWidth;
	(void)x;
	(void)drawStart;
	(void)drawEnd;
	int y = 0;

	val->mlx = mlx_init();
	val->win = mlx_new_window(val->mlx, 1000, 1000, "porfa pinta cosas");
	val->img = mlx_new_image(val->mlx, 1000, 1000);
	val->img_addr = (int*)mlx_get_data_addr(val->img, &val->bpp, &val->line, &val->endian);
	while (y++ < 1000)
		val->img_addr[y * 640 + 500] = 0x00FF0000;
	mlx_put_image_to_window(val->mlx, val->win, val->img, 0, 0);
	mlx_loop(val->mlx);
}

int main()
{
	t_id val;

	double posX = 22, posY = 12;  //x and y start position (GET FROM PARSE MAP)
	double dirX = -1, dirY = 0; //initial direction vector (DEFINE AS DEFAULT)
	double planeX = 0, planeY = 0.66; //the 2d raycaster version of camera plane

	//	double time = 0; //time of current frame
	//	double oldTime = 0; //time of previous frame
	//mlx_new_window(var.mlx, screenWidth, screenHeight, "Raycaster");

	//which box of the map we're in
	int mapX = (int)posX;
	int mapY = (int)posY;

	//length of ray from current position to next x or y-side
	double sideDistX;
	double sideDistY;


	//what direction to step in x or y-direction (either +1 or -1)
	int stepX;
	int stepY;

	int hit = 0; //was there a wall hit?
	int side; //was a NS or a EW wall hit?

	//while(!done())
	//{
	int x = 100;
	if (x++ < 1000)
	{
		//calculate ray position and direction
		double cameraX = 2 * x / (double)mapWidth - 1; //x-coordinate in camera space
		double rayDirX = dirX + planeX * cameraX;
		double rayDirY = dirY + planeY * cameraX;

		//length of ray from one x or y-side to next x or y-side
		//			HAY QUE CONTROLAR PARA QUE CUANDO DIVIDA ENTRE 0 EL COCIENTE
		//			DE 0 AUTOMÁTICAMENTE (FLOATING POINT EXCEPTION)
		double deltaDistX = rayDirX == 0 ? 0 : sqrt(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX));
		double deltaDistY = rayDirY == 0 ? 0 : sqrt(1 + (rayDirX * rayDirX) / (rayDirY * rayDirY));
		double perpWallDist;

		//calculate step and initial sideDist
		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (posX - mapX) * deltaDistX;//posX is a double, mapX an 
		}//											int, so pos - map is 0.n
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - posX) * deltaDistX;//with this, we've got
		}//												the "oposite" value, if
		if (rayDirY < 0)//								we had 0.2 above, here
		{//												it is 0.8
			stepY = -1;
			sideDistY = (posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - posY) * deltaDistY;
		}
		//perform DDA
		while (hit == 0)
		{
			//jump to next map square, OR in x-direction, OR in y-direction
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			//Check if ray has hit a wall
			hit = worldMap[mapX][mapY] > 0 ? 1 : 0;
		}
		//Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
		if (side == 0)
			perpWallDist = (mapX - posX + (1 - stepX) / 2) / rayDirX;
		else
			perpWallDist = (mapY - posY + (1 - stepY) / 2) / rayDirY;

		//Calculate height of line to draw on screen
		int lineHeight = (int)(wallHeight / perpWallDist);

		//Calculate lowest and highest pixel to fill in current stripe
		int drawStart = wallHeight / 2 - lineHeight / 2;

		if(drawStart < 0)//I don't really understand why you need to check this
			drawStart = 0;

		int drawEnd = wallHeight / 2 + lineHeight / 2;

		if(drawEnd >= wallHeight)//Same as before, is this condition ever true?
			drawEnd = wallHeight - 1;

//		draw_background(&val);
		draw_column(x, drawStart, drawEnd, &val);

		printf("posX %f  posY %f\ndirX %f  dirY %f\nmapX %d mapY %d\nplaneX %f  planeY %f\n", posX, posY, dirX, dirY, mapX, mapY, planeX, planeY);
		printf("rayDirX %f  rayDirY %f\nsideDistX %f  sideDistY %f\nDeltaX %f  DeltaY %f\nstepX %d  stepY %d\n", rayDirX, rayDirY, sideDistX, sideDistY, deltaDistX, deltaDistY, stepX, stepY);
		printf("wallDist %f\nlineHeigth %d\ndrawStart %d\ndrawEnd %d\n", perpWallDist, lineHeight, drawStart, drawEnd);
		printf("\n\n");
	}
	return (0);
}

//choose wall color.....To be continued.
