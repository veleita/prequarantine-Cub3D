#include <mlx.h>
#include <math.h>
#include <stdio.h>

#define mapWidth 24
#define mapHeight 24
#define screenWidth 1000
#define screenHeight 1000
#define wallHeight 24

typedef struct s_id
{
	void		*mlx;
	void		*win;
	void		*img;
	int		*img_addr;
	int			bpp;
	int			line;
	int			endian;
}				t_id;

int worldMap[mapHeight][mapWidth]=
{
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,9,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
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

void	draw_column(int x, int drawStart, int drawEnd, t_id *val)
{
	int y = drawStart - 1;

	//printf("drawStart = %d\ndrawEnd = %d\n", drawStart, drawEnd);
	//printf("\n");
	while (++y <= drawEnd)
		val->img_addr[y * screenWidth + x] = 0x00FF0000;
}

int main()
{
	t_id val;

	double posX = 6, posY = 9;  //x and y start position (GET FROM PARSE MAP)
	double dirX = -1, dirY = 0; //initial direction vector (DEFINE AS DEFAULT)
	double planeX = 0, planeY = 0.66; //the 2d raycaster version of camera plane

	int mapX = (int)posX;
	int mapY = (int)posY;


	int stepX;
	int stepY;

	double sideDistX;
	double sideDistY;

	val.mlx = mlx_init();
	val.win = mlx_new_window(val.mlx, screenWidth, screenHeight, "porfa pinta cosas");
	val.img = mlx_new_image(val.mlx, mapWidth, mapHeight);
	val.img_addr = (int*)mlx_get_data_addr(val.img, &val.bpp, &val.line, &val.endian);

/*	int y = -1;
	int x;
	while (++y < 24)
	{
		x = -1;
		while (++x < 24)
			printf("%d ", worldMap[x][y]);
		printf("\n");
	}*/
	int x = -1;
	while (++x < mapWidth)
	{
		double cameraX = 2 * x / (double)mapWidth - 1;

		double rayDirX = dirX + planeX * cameraX;
		double rayDirY = dirY + planeY * cameraX;

		double deltaDistX = rayDirX == 0 ? 0 : sqrt(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX));
		double deltaDistY = rayDirY == 0 ? 0 : sqrt(1 + (rayDirX * rayDirX) / (rayDirY * rayDirY));

		//printf("deltaX = %f deltaT = %f\n", deltaDistX, deltaDistY);
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
		int hit = 0;
		int side = 0;
		double perpWallDist;
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
			printf("mapx = %d mapY = %d\n", mapX, mapY);
			printf("map = %d\n", worldMap[mapX][mapY]);
			hit = worldMap[mapX][mapY] > 0 ? 1 : 0;
		}
		//Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
		if (side == 0)
			perpWallDist = (mapX - posX + (1 - stepX) / 2) / rayDirX;
		else
			perpWallDist = (mapY - posY + (1 - stepY) / 2) / rayDirY;

		if (perpWallDist < 0)
			perpWallDist = 1000;
		else if (perpWallDist == 0)
			perpWallDist = 1;
		//Calculate height of line to draw on screen
		int lineHeight = (int)(wallHeight / perpWallDist);

		//Calculate lowest and highest pixel to fill in current stripe
		int drawStart = wallHeight / 2 - lineHeight / 2;

		if(drawStart < 0)
			drawStart = 0;

		int drawEnd = wallHeight / 2 + lineHeight / 2;

		if(drawEnd >= wallHeight)
			drawEnd = wallHeight - 1;

		//printf("x = %d perpWallDist = %f lineHeigth = %d\n", x, perpWallDist, lineHeight);
		draw_column(x, drawStart, drawEnd, &val);
	}
	mlx_put_image_to_window(val.mlx, val.win, val.img, 0, 0);
	mlx_loop(val.mlx);
	return (0);
}
