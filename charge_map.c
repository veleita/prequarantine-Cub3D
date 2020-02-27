#include "cub3D.h"

static t_camera	*set_dir_plane(double dirX, double dirY, 
		double planeX, double planeY)
{
	t_camera *camera;

	if (!(camera = (t_camera*)malloc(sizeof(t_camera))))
		exit(0);
	camera->dir_x = dirX;
	camera->dir_y = dirY;
	camera->plane_x = planeX;
	camera->plane_y = planeY;
	return (camera);
}

t_camera	check_coord(char coord, t_map *map, int y, t_var *var)
{
	t_camera *camera;

	if (coord == 'N')
		camera = set_dir_plane(0, -1, 0.66, 0);
	if (coord == 'S')
		camera = set_dir_plane(0, 1, -0.66, 0);
	if (coord == 'E')
		camera = set_dir_plane(1, 0, 0, -0.66);
	if (coord == 'W')
		camera = set_dir_plane(-1, 0, 0, 0.66);
	var->pos_x = map->x + 0.5;
	var->pos_y = y + 0.5;
	return (*camera);
}

void	fill_map(char *line, int **map, int x)
{
	int		it;
	int		y;

	it = 0;
	y = 0;
	//printf("\nline %s\n\n", line);
	while (line[it] != '\0')
	{
		if (ft_isdigit(line[it]))
		{
			map[x][y] = line[it] - 48;
			//printf("%d ", map[x][y]);
			y++;
		}
		else if (ft_isalpha(line[it]))
		{
			map[x][y] = 0;
			//printf("%d ", map[x][y]);
			y++;
		}
		it++;
	}
}

int	**create_map(char *file_name, int x, int y)
{
	int		**map;
	int		fd;
	char	*line;

	x -= 1;
	if (!(map = (int**)malloc(x * sizeof(int*))))
		return (0);
	fd = open(file_name, O_RDONLY);
	while (x >= 0)
	{
		get_next_line(fd, &line);
		if (ft_strnstr(line, "1 ", y))
		{
			if (!(map[x] = (int*)malloc(y * sizeof(int))))
				return (0);
			fill_map(line, map, x);
			printf("\n");
			x--;
		}
	}
	//if (!(map[x] = (int*)malloc(y * sizeof(int))))
	//	return (0);
	//fill_map(line, map, x);
	//printf("end\n");
	/*if (len == 0)
	  {
	  if (!(map[y] = (int*)malloc(x * sizeof(int))))
	  return (0);
	  fill_map(line, map, y);
	  }
	  else
	  return (0);*/
	return (map);
}

