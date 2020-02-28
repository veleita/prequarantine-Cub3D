#include "cub3D.h"

static void		init_map(t_map *map)
{
	map->resolution_x = 0;
	map->resolution_y = 0;
	map->no = NULL;
	map->ea = NULL;
	map->we = NULL;
	map->so = NULL;
	map->sprt = NULL;
	map->floor_rgb.r = 0;
	map->floor_rgb.g = 0;
	map->floor_rgb.b = 0;
	map->ceiling_rgb.r = 0;
	map->ceiling_rgb.g = 0;
	map->ceiling_rgb.b = 0;
	map->x = 0;
	map->y = 0;
}

static int	get_resolution(char *line, t_map *map)
{
	int it;

	if (map->resolution_x != 0 || map->resolution_y != 0)
		return (0);
	it = 0;
	while (line[it] == ' ' && line[it + 1] != '\0')
		it++;
	if (!(line[it++] == 'R'))
		return (0);
	else
	{
		while (line[it] == ' ' && line[it + 1] != '\0')
			it++;
		while (ft_isdigit(line[it]))
		{
			map->resolution_x = map->resolution_x * 10 + line[it] - '0';
			it++;
		}
		while (line[it] == ' ' && line[it + 1] != '\0')
			it++;
		while (ft_isdigit(line[it]))
		{
			map->resolution_y = map->resolution_y * 10 + line[it] - '0';
			it++;
		}
	}
	if (10 >= map->resolution_x || 10 >= map->resolution_y)
		return (0);
	map->resolution_x = map->resolution_x > 2560 ? 2560 : map->resolution_x;
	map->resolution_y = map->resolution_y > 1440 ? 1440 : map->resolution_y;
	return (1);
}

static char		*get_path(char *line, char first, char second)
{
	int it;
	int len;
	char *ret;

	it = 0;
	remove_space(line, &it);
	if (!(line[it] == first && line[it + 1] == second))
		return (NULL);
	else
	{
		len = 0;
		it += 2;
		remove_space(line, &it);
		while (line[it] != ' ')
		{
			len++;
			it++;
		}
		if (!(ret = (char*)malloc(len + 1)))
			return (0);
		ret[len] = '\0';
		while (len >= 0)
			ret[len--] = line[it--];
	}
	return (ret);
}

static t_color	get_color(char *line)
{
	int			it;
	t_color		ret;

	ret.r = 0;
	ret.g = 0;
	ret.b = 0;
	it = 0;
	remove_space(line, &it);
	if (line[it++] != 'F' && line[it - 1] != 'C')
		exit(0);
	remove_space(line, &it);
	while (ft_isdigit(line[it++]))
		ret.r = ret.r * 10 + line[it - 1] - '0';
	while (ft_isdigit(line[it++]))
		ret.g = ret.g * 10 + line[it - 1] - '0';
	while (ft_isdigit(line[it++]))
		ret.b = ret.b * 10 + line[it - 1] - '0';
	if ((0 > ret.r || ret.r > 255) || (0 > ret.g|| ret.g > 255) ||
	  (0 > ret.b || ret.b > 255))
		exit(0);
	return (ret);
}

static	int	map_at_the_bottom(t_map *map)
{
	if ((map->ceiling_rgb.r == 0 && map->ceiling_rgb.g == 0 &&
				map->ceiling_rgb.b == 0) || (map->floor_rgb.r == 0 &&
					map->floor_rgb.g == 0 && map->floor_rgb.b == 0)
			|| map->sprt == 0 || map->so == 0 || map->we == 0 || map->ea == 0
			|| map->no == 0 || map->resolution_x == 0 || map->resolution_y == 0
			|| map->x != 0)
		return (0);//missing information before reading the 2D map, did you
	else//forget something? Remember that your map should be at the
		return (1);//botom of the file.`
}

static	void	first_and_last_line(char *line, int it, t_map *map)
{
	while (line[it] == ' ' || line[it] == '1')
	{
		if (line[it] == ' ')
			it++;
		if (line[it++] == '1')
			(map->y)++;
	}
}

static int	evaluate_map(char *line, int fd, t_map *map, t_var *var)
{
	int	it;
	int	y;
	int	len;
	int	player;

	if (map_at_the_bottom(map) == 0)
		exit(0);
	player = 0;
	first_and_last_line(line, 0, map);
	map->x++;
	line = 0;
	while ((len = get_next_line(fd, &line) > 0))
	{
		y = 0;
		it = 0;
		remove_space(line, &it);
		while (line[it] == '0' || line[it] == '1' || line[it] == '2' ||
				line[it] == 'N' || line[it] == 'S' || line[it] == 'W' ||
				line[it] == 'E' || line[it] == ' ')
		{
			if (ft_isalpha(line[it]))
			{
				if (player == 1)
					exit(0);
				player = 1;
				var->camera = check_coord(line[it], map, y, var);
			}
			if (line[it++] != ' ')
				y++;
			if ((y == 1 || y == map->y) && line[it - 1] == 0)
				exit(0);
		}
		if (y != map->y)//our map would not be rectangular
			return (0);
		map->x++;
	}
	return (1);
}

t_map	read_map(char *file_name, t_var *var, int fd)
{
	char **line;
	t_map *map;
	int len = 0;

	if (!(line = (char**)malloc(sizeof(char*))))
		exit(0);
	if (!(map = (t_map*)malloc(sizeof(t_map))))
		exit(0);
	init_map(map);
	while ((len = get_next_line(fd, line) > 0))
	{
		if (ft_strchr(*line, 'R'))
		{
			if (!(get_resolution(*line, map)))
				exit(0);
		}
		else if (ft_strnstr(*line, "NO", ft_strlen(*line)/4))
		{
			if (!(map->no = get_path(*line, 'N', 'O')))
				exit(0);
		}
		else if (ft_strnstr(*line, "EA", ft_strlen(*line)/4))
		{
			if (!(map->ea = get_path(*line, 'E', 'A')))
				exit(0);
		}
		else if (ft_strnstr(*line, "WE", ft_strlen(*line)/4))
		{
			if (!(map->we = get_path(*line, 'W', 'E')))
				exit(0);
		}
		else if (ft_strnstr(*line, "SO", ft_strlen(*line)/4))
		{
			if (!(map->so = get_path(*line, 'S', 'O')))
				exit(0);
		}
		else if (ft_strnstr(*line, "S", ft_strlen(*line)/4))
		{
			if (!(map->sprt = get_path(*line, 'S', ' ')))
				exit(0);
		}
		else if (ft_strnstr(*line, "F", ft_strlen(*line)/10))
		{
			if (map->floor_rgb.r != 0 || map->floor_rgb.g != 0 ||
					map->floor_rgb.b != 0)
				exit(0);
			map->floor_rgb = get_color(*line);
		}
		else if (ft_strnstr(*line, "C", ft_strlen(*line)/10))
		{
			if (map->ceiling_rgb.r != 0 || map->ceiling_rgb.g != 0 ||
					map->ceiling_rgb.b != 0)
				exit(0);
			map->ceiling_rgb = get_color(*line);
		}
		else if (ft_strchr(*line, '1'))
		{
			if (evaluate_map(*line, fd, map, var) != 1)
				exit(0);
		}
	free(*line);
	}
	free(line);
	close(fd);
	map->map = create_map(file_name, map->x, map->y);
	return (*map);
}
