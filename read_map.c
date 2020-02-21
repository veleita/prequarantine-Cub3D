#include "cub3D.h"

static int		init_map(t_map *map)
{
	map->resolutionX = 0;
	map->resolutionY = 0;
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
	return (1);
}

static int	get_resolution(char *line, t_map *map)
{
	int it;

	if (map->resolutionX != 0 || map->resolutionY != 0)
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
			map->resolutionX = map->resolutionX * 10 + line[it] - '0';
			it++;
		}
		while (line[it] == ' ' && line[it + 1] != '\0')
			it++;
		while (ft_isdigit(line[it]))
		{
			map->resolutionY = map->resolutionY * 10 + line[it] - '0';
			it++;
		}
	}
	if (10 >= map->resolutionX || 10 >= map->resolutionY)
		return (0);
	if (map->resolutionX > 2560)
		map->resolutionX = 2560;
	if (map->resolutionY > 1440)
		map->resolutionX = 1440;
	return (1);
}

static char		*get_path(char *line, char first, char second)
{
	int it;
	int len;
	char *ret;

	it = 0;
	while (line[it] == ' ')
		it++;
	if (!(line[it] == first && line[it + 1] == second))
		return (NULL);
	else
	{
		len = 0;
		it += 2;
		while (line[it] == ' ')
			it++;
		while (line[it] != ' ')
		{
			len++;
			it++;
		}
		if (!(ret = (char*)malloc(len + 1)))
			return (0);
		it -= len;
		len = 0;
		while (line[len] != '\0')
		{
			ret[len] = line[it];
			len++;
			it++;
		}
		ret[len] = '\0';
	}
	if (ret[0] == '\0')
		return (NULL);
	return (ret);
}

static t_color	get_color(char *line)
{
	int			it;
	t_color		ret;

	ret.r = 0;
	ret.g = 0;
	ret.b = 0;
	//ret = (t_color)malloc(sizeof(t_color));//HAY QUE PROTEGER ESTE MALLOC (FT_EXIT)
	it = 0;
	while (line[it] == ' ')
		it++;
	if (line[it] == 'F' || line[it] == 'C')
		it++;
	while (line[it] == ' ' && line[it + 1] != '\0')
		it++;
	while (ft_isdigit(line[it]))
	{
		ret.r = ret.r * 10 + line[it] - '0';
		it++;
	}
	it++;
	while (ft_isdigit(line[it]))
		ret.g = ret.g * 10 + line[it++] - '0';
	it++;
	while (ft_isdigit(line[it]))
		ret.b = ret.b * 10 + line[it++] - '0';
	//}
		/*if ((0 > ret.r || ret.r > 255) || (0 > ret.g|| ret.g > 255) ||
		  (0 > ret.b || ret.b > 255))
		  return (0);CONTROL DE ERRORES AQUI (FT_EXIT)*/
	return (ret);
}

static int	evaluate_map(char *line, int fd, t_map *map, t_var *var)
{
	int it;
	int x;
	int len;

	if ((map->ceiling_rgb.r == 0 && map->ceiling_rgb.g == 0 &&
				map->ceiling_rgb.b == 0) || (map->floor_rgb.r == 0 &&
					map->floor_rgb.g == 0 && map->floor_rgb.b == 0)
			|| map->sprt == 0 || map->so == 0 || map->we == 0 || map->ea == 0
			|| map->no == 0 || map->resolutionX == 0 || map->resolutionY == 0
			|| map->x != 0)
	{
		return (0);//missing information before reading the 2D map, did you
	//forget something? Remember that your map should be at the
	//bottom of the file.
	}
	it = 0;
	while (line[it] == ' ' || line[it] == '1')
	{
		if (line[it] == ' ')
			it++;
		if (line[it++] == '1')
			(map->x)++;
	}
	map->y++;
	line = 0;
	while ((len = get_next_line(fd, &line) > 0))
	{
		x = 0;
		it = 0;
		while (line[it] == ' ')
			++it;
		while (line[it] == '0' || line[it] == '1' || line[it] == '2' ||
				line[it] == 'N' || line[it] == 'S' || line[it] == 'W' ||
				line[it] == 'E' || line[it] == ' ')
		{
			//printf("%c ", line[it]);
			if (ft_isalpha(line[it]))
			{
				//printf("gdgfs");
				var->camera = check_coord(line[it], map, x, var);
			}
			if (line[it++] != ' ')
				x++;
		}
		if (x != map->x)//our map would not be rectangular
			return (0);
		map->y++;
	}
	/*if (len == 0)
	{
		while (line[it] == ' ')
			++it;
		if (line[++it] != '1' && line[it] != ' ')
			return (0);
	}*/
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
			if (map->floor_rgb.r != 0 || map->floor_rgb.g != 0 || map->floor_rgb.b != 0)
				exit(0);
			map->floor_rgb = get_color(*line);
		}
		else if (ft_strnstr(*line, "C", ft_strlen(*line)/10))
		{
			if (map->ceiling_rgb.r != 0 || map->ceiling_rgb.g != 0 || map->ceiling_rgb.b != 0)
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
