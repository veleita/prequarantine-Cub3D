#include "cub3D.h"

static t_camera	*set_dir_plane(double dirX, double dirY, 
		double planeX, double planeY)
{
	t_camera *camera;

	if (!(camera = (t_camera*)malloc(sizeof(t_camera))))
		exit(0);
	camera->dirX = dirX;
	camera->dirY = dirY;
	camera->planeX = planeX;
	camera->planeY = planeY;
	return (camera);
}

t_camera	check_coord(char coord, t_map *map, int x, t_var *var)
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
	var->posx = x + 0.5;
	var->posy = map->y + 0.5;
	return (*camera);
}

void	fill_map(char *line, int **map, int y)
{
	int		it;
	int		x;

	it = 0;
	x = 0;
	while (line[it] != '\0')
	{
		if (ft_isdigit(line[it]))
		{
			map[y][x] = line[it] - '0';
			x++;
		}
		else if (ft_isalpha(line[it]))
		{
			map[y][x] = 0;
			x++;
		}
		it++;
	}
}

int	**create_map(char *file_name, int x, int y)
{
	int		**map;
	int		fd;
	char	*line;

	if (!(map = (int**)malloc(y * sizeof(int*))))
		return (0);
	fd = open(file_name, O_RDONLY);
	while (y > 0)
	{
		get_next_line(fd, &line);
		if (ft_strnstr(line, "1 ", x))
		{
			if (!(map[y] = (int*)malloc(x * sizeof(int))))
				return (0);
			fill_map(line, map, y);
			y--;
		}
	}
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

