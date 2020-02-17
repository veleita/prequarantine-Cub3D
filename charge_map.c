#include "cub3D.h"

static void	set_dir_plane(	t_var *var, double dirX, double dirY, 
		double planeX, double planeY)
{
	var->dirX = dirX;
	var->dirY = dirY;
	var->planeX = planeX;
	var->planeY = planeY;
}

int	check_coord(char coord, t_map *map, int x, t_var *var)
{
	if (var->dirX != 0 || var->dirY != 0 || 
			var->planeX != 0 || var->planeY != 0)
		return (0);
	if (coord == 'N')
		set_dir_plane(var, 0, -1, 0.66, 0);
	if (coord == 'S')
		set_dir_plane(var, 0, 1, -0.66, 0);
	if (coord == 'E')
		set_dir_plane(var, 1, 0, 0, -0.66);
	if (coord == 'W')
		set_dir_plane(var, -1, 0, 0, 0.66);
	var->posx = x + 0.5;
	var->posy = map->y + 0.5;
	return (1);
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
	int		len;

	if (!(map = (int**)malloc(y * sizeof(int*))))
		return (0);
	fd = open(file_name, O_RDONLY);
	y = 0;
	while ((len = get_next_line(fd, &line)) > 0)
	{
		if (ft_strnstr(line, "1 1", x))
		{
			if (!(map[y] = (int*)malloc(x * sizeof(int))))
				return (0);
			fill_map(line, map, y);
			y++;
		}
	}
	if (len == 0)
	{
			if (!(map[y] = (int*)malloc(x * sizeof(int))))
				return (0);
		fill_map(line, map, y);
	}
	else
		return (0);
	return (map);
}

