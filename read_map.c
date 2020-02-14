#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int		ft_strlen(const char *str)
{
	int cont;

	cont = 0;
	while (*(str++) != '\0')
		cont++;
	return (cont);
}

int		ft_isdigit(int c)
{
	if ('0' <= c && c <= '9')
		return (1);
	else
		return (0);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*pdst;
	const char	*psrc;

	pdst = (char*)dst;
	psrc = (const char*)src;
	if (src == dst)
		return (dst);
	while (n)
	{
		*(pdst++) = *(psrc++);
		n--;
	}
	return (dst);
}

char	*ft_strdup(const char *s1)
{
	char	*s2;

	if ((s2 = malloc(ft_strlen(s1) + 1)))
	{
		ft_memcpy(s2, s1, ft_strlen(s1) + 1);
		return (s2);
	}
	else
		return (NULL);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ret;
	size_t	retlen;
	size_t	it;
	size_t	slen;

	slen = ft_strlen(s);
	if (!s)
		return (NULL);
	if (slen < start)
		return (ft_strdup(""));
	retlen = slen - start > len ? len : slen - start;
	if (!(ret = malloc(retlen + 1)))
		return (NULL);
	it = 0;
	while (it < retlen)
		ret[it++] = s[start++];
	ret[it] = '\0';
	return (ret);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ret;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	if (!(ret = malloc(ft_strlen(s1) + ft_strlen(s2) + 1)))
		return (NULL);
	i = -1;
	while (s1[++i])
		ret[i] = s1[i];
	j = -1;
	while (s2[++j])
		ret[i++] = s2[j];
	ret[i] = '\0';
	return (ret);
}

static int	ft_strchr(char *s, char c)
{
	int	it;

	it = 0;
	while (s[it])
	{
		if (s[it++] == c)
			return (it);
	}
	return (0);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	unsigned int ith;
	unsigned int itn;

	if (!*needle)
		return ((char*)haystack);
	ith = 0;
	while (haystack[ith] != '\0' && (size_t)ith < len)
	{
		if (haystack[ith] == needle[0])
		{
			itn = 1;
			while (needle[itn] != '\0' && haystack[itn + ith] == needle[itn] &&
					(size_t)(ith + itn) < len)
				itn++;
			if (needle[itn] == '\0')
				return ((char*)&haystack[ith]);
		}
		ith++;
	}
	return (NULL);
}

static int	empty(char **line)
{
	*line = ft_strdup("");
	return (0);
}

static int	get_line(char **file, int fd, char **line)
{
	char	*tmp;
	int		it;

	if ((it = ft_strchr(file[fd], '\n')))
	{
		*line = ft_substr(file[fd], 0, it - 1);
		tmp = ft_strdup(&((file[fd])[it]));
		free(file[fd]);
		file[fd] = tmp;
	}
	else
	{
		*line = ft_strdup(file[fd]);
		free(file[fd]);
		file[fd] = NULL;
		return (0);
	}
	return (1);
}

int			get_next_line(int fd, char **line)
{
	char			*buffer;
	static char		*file[4096];
	int				len;
	char			*tmp;

	if (!line || fd < 0 || !(buffer = (char *)malloc(100)))
		return (-1);
	while ((len = read(fd, buffer, 100)) > 0)
	{
		buffer[len] = '\0';
		if (file[fd] == NULL)
			file[fd] = ft_strdup(buffer);
		else
		{
			tmp = ft_strjoin(file[fd], buffer);
			free(file[fd]);
			file[fd] = tmp;
		}
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	free(buffer);
	if (len < 0)
		return (-1);
	return ((len == 0 && !file[fd]) ? empty(line) : get_line(file, fd, line));
}

typedef struct s_color
{
	int r;
	int g;
	int b;
}		t_color;

typedef struct s_map
{
	int resolutionX;
	int resolutionY;
	char *no;
	char *ea;
	char *we;
	char *so;
	char *sprt;
	t_color *floor;
	t_color *ceiling;
	int x;
	int y;
}		t_map;

void	init_map(t_map *map)
{
	map->resolutionX = 0;
	map->resolutionY = 0;
	map->no = 0;
	map->ea = 0;
	map->we = 0;
	map->so = 0;
	map->sprt = 0;
/*	map->floor->r = 0;
	map->floor->g = 0;
	map->floor->b = 0;
	map->ceiling->r = 0;
	map->ceiling->g = 0;
	map->ceiling->b = 0;*/
	map->x = 0;
	map->y = 0;
}

int	get_resolution(char *line, t_map *map)
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

int	get_NO_texture(char *line, t_map *map)
{
	int it;
	int len;

	if (map->no != 0)
		return (0);
	it = 0;
	while (line[it] == ' ' && line[it + 1] != '\0')
		it++;
	if (!(line[it] == 'N' && line[it + 1] == 'O'))
		return (0);
	else
	{
		len = 0;
		it += 2;
		while (line[it] == ' ' && line[it + 1] != '\0')
			it++;
		while (line[it] != ' ')
		{
			len++;
			it++;
		}
		if (!(map->no = (char*)malloc((len + 1)*sizeof(char))))
			return(-1);
		it -= len;
		len = 0;
		while (line[it] != ' ')
		{
			map->no[len] = line[it];
			len++;
			it++;
		}
		map->no[len] = '\0';
	}
	if (map->no[0] == '\0')
		return (0);
	return (1);
}

int	get_EA_texture(char *line, t_map *map)
{
	int it;
	int len;

	if (map->ea != 0)
		return (0);
	it = 0;
	while (line[it] == ' ' && line[it + 1] != '\0')
		it++;
	if (!(line[it] == 'E' && line[it + 1] == 'A'))
		return (0);
	else
	{
		len = 0;
		it += 2;
		while (line[it] == ' ' && line[it + 1] != '\0')
			it++;
		while (line[it] != ' ')
		{
			it++;
			len++;
		}
		if (!(map->ea = (char*)malloc((len + 1)*sizeof(char))))
			return(-1);
		it -= len;
		len = 0;
		while (line[len] != '\0')
		{
			map->ea[len] = line[it];
			len++;
			it++;
		}
		map->ea[len] = '\0';
	}
	if (map->ea[0] == '\0')
		return (0);
	return (1);
}

int	get_WE_texture(char *line, t_map *map)
{
	int it;
	int len;

	//printf("%s", line);
	if (map->ea != 0)
		return (0);
	it = 0;
	while (line[it] == ' ')
		it++;
	if (!(line[it] == 'W' && line[it + 1] == 'E'))
		return (0);
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
		if (!(map->we = (char*)malloc((len + 1)*sizeof(char))))
			return(-1);
		it -= len;
		len = 0;
		while (line[len] != '\0')
		{
			map->we[len] = line[it];
			len++;
			it++;
		}
		map->we[len] = '\0';
	}
	if (map->we[0] == '\0')
		return (0);
	return (1);
}

int	get_SO_texture(char *line, t_map *map)
{
	int it;
	int len;

	if (map->ea != 0)
		return (0);
	it = 0;
	while (line[it] == ' ' && line[it + 1] != '\0')
		it++;
	if (!(line[it] == 'S' && line[it + 1] == 'O'))
		return (0);
	else
	{
		len = 0;
		it += 2;
		while (line[it] == ' ' && line[it + 1] != '\0')
			it++;
		while (line[it] != ' ')
		{
			len++;
			it++;
		}
		if (!(map->so = (char*)malloc((len + 1)*sizeof(char))))
			return(-1);
		it -= len;
		len = 0;
		while (line[it] != ' ')
		{
			map->so[len] = line[it];
			len++;
			it++;
		}
		map->so[len] = '\0';
	}
	if (map->so[0] == '\0')
		return (0);
	return (1);
}

int	get_sprite(char *line, t_map *map)
{
	int it;
	int len;

	if (map->sprt != 0)
		return (0);
	it = 0;
	while (line[it] == ' ' && line[it + 1] != '\0')
		it++;
	if (line[it++] == 'E')
		return (0);
	else
	{
		len = 0;
		while (line[it] == ' ' && line[it + 1] != '\0')
			it++;
		while (line[it] != ' ')
		{
			it++;
			len++;
		}
		if (!(map->sprt = (char*)malloc((len + 1)*sizeof(char))))
			return(-1);
		it -= len;
		len = 0;
		while (line[it] != ' ')
		{
			map->sprt[len] = line[it];
			len++;
			it++;
		}
		map->sprt[len] = '\0';
	}
	if (map->sprt[0] == '\0')
		return (0);
	return (1);
}

int	get_floor(char *line, t_map *map)
{
	int it;

	printf("F %d %d %d\n", map->floor->r, map->floor->g, map->floor->b);
	if (map->floor->r != 0 || map->floor->g != 0 || map->floor->b != 0)
		return (0);
	it = 0;
	while (line[it] == ' ' && line[it + 1] != '\0')
		it++;
	if (!(line[it++] == 'F'))
		return (0);
	else
	{
		while (line[it] == ' ' && line[it + 1] != '\0')
			it++;
		while (ft_isdigit(line[it++]))
			map->floor->r += map->floor->r * 10 + line[it] - '0';
		it++;
		while (ft_isdigit(line[it++]))
			map->floor->g += map->floor->g * 10 + line[it] - '0';
		it++;
		while (ft_isdigit(line[it++]))
			map->floor->b += map->floor->b * 10 + line[it] - '0';
	}
	if ((0 > map->floor->r || map->floor->r > 255) ||
			(0 > map->floor->g || map->floor->g > 255) ||
			(0 > map->floor->b || map->floor->b > 255))
		return (0);
	return (1);
}

int	get_ceiling(char *line, t_map *map)
{
	int it;

	if (map->ceiling->r != 0 || map->ceiling->g != 0 || map->ceiling->b != 0)
		return (0);
	it = 0;
	while (line[it] == ' ' && line[it + 1] != '\0')
		it++;
	if (!(line[it++] == 'C'))
		return (0);
	else
	{
		while (line[it] == ' ' && line[it + 1] != '\0')
			it++;
		while (ft_isdigit(line[it++]))
			map->ceiling->r += map->ceiling->r * 10 + line[it] - '0';
		it++;
		while (ft_isdigit(line[it++]))
			map->ceiling->g += map->ceiling->g * 10 + line[it] - '0';
		it++;
		while (ft_isdigit(line[it++]))
			map->ceiling->b += map->ceiling->b * 10 + line[it] - '0';
	}
	if ((0 > map->ceiling->r || map->ceiling->r > 255) ||
			(0 > map->ceiling->g || map->ceiling->g > 255) ||
			(0 > map->ceiling->b || map->ceiling->b > 255))
		return (0);
	return (1);
}

int	get_map(char *line, int fd, t_map *map)
{
	int it;
	int x;

	if ((map->ceiling->r == 0 && map->ceiling->g == 0 && map->ceiling->b == 0) ||
			(map->floor->r == 0 && map->floor->g == 0 && map->floor->b == 0) ||
			map->sprt == 0 || map->so == 0 || map->we == 0 || map->ea == 0 ||
			map->no == 0 || map->resolutionX == 0 || map->resolutionY == 0 ||
			map->x != 0 || map != 0)
		return (0);//missing information before reading the 2D map, did you forget something? Remember that your map should be at the bottom of the file.
	it = 0;
	while (line[it] == ' ')
		it++;
	if (line[it] != '1')
		return (0);
	map->x = it;
	while (line[map->x] == '1')
		map->x++;
	if (line[map->x])//that would mean that the last element of the line is not '1'
		return (0);
	map->x -= it;
	map->y++;
	while ((get_next_line(fd, &line) > 0))
	{
		while (line[it] == ' ')
			it++;
		x = it;
		while (line[x] == '0' || line[x] == '1' || line[x] == '2' ||
				line[x] == 'N' || line[x] == 'S' || line[x] == 'W' ||
				line[x] == 'E')
		{
			/*if (ft_isalpha(line[x]))
			{
				if (!get_dir(line[x]))
					return (0);//incorrect or duplicated dir value
			}*/
			x++;
		}
		x -= it;
		if (x != map->x)//our map would not be rectangular
			return (0);
		map->y++;
	}
	if ((get_next_line(fd, &line) == 0))
	{
		while (line[it] == ' ')
			it++;
		if (line[it] != '1')
			return (0);
	}
	return (0);
}

int main(int argc, char **argv)
{
	//char *line = 0;
	//int fd = open(argv[1], O_RDONLY);
	t_map *map;
	(void)argv;
	(void)argc;
	int len = 0;

	if (!(map = (t_map*)malloc(sizeof(t_map))))
		return (0);
	init_map(map);
	/*while ((len = get_next_line(fd, &line) > 0))
	{
		printf("line = %s\n", line);
		if (ft_strchr(line, 'R'))
		{
			printf("r\n");
			if (!(get_resolution(line, map)))
				return (0);
			printf("resolutionX %d  resolutionY %d\n", map->resolutionX, map->resolutionY);
		}
		else if (ft_strnstr(line, "NO", ft_strlen(line)/4))
		{
			printf("no\n");
			if (!(get_NO_texture(line, map)))
				return (0);
			printf("NO %s\n", map->no);
		}
		else if (ft_strnstr(line, "EA", ft_strlen(line)/4))
		{
			printf("ea\n");
			if (!(get_EA_texture(line, map) == 1))
				return (0);
			printf("EA %s\n", map->ea);
		}
		else if (ft_strnstr(line, "WE", ft_strlen(line)/4))
		{
			printf("we\n");
			if (!(get_WE_texture(line, map) == 1))
				return (0);
			printf("WE %s\n", map->we);
		}
		else if (ft_strnstr(line, "SO", ft_strlen(line)/4))
		{
			printf("so\n");
			if (!(get_SO_texture(line, map) == 1))
				return (0);
			printf("SO %s\n", map->so);
		}
		else if (ft_strnstr(line, "S", ft_strlen(line)/4))
		{
			printf("s\n");
			//if (!(get_sprite(line, map) == 1))
			//	return (0);
			printf("S %s\n", map->sprt);
		}
		else if (ft_strnstr(line, "F", ft_strlen(line)/4))
		{
			printf("f\n");
			//if (!(get_floor(line, map) == 1))
			//	return (0);
			//printf("F %d %d %d\n", map->floor->r, map->floor->g, map->floor->b);
		}
		else if (ft_strnstr(line, "C", ft_strlen(line)/4))
		{
			printf("c\n");
			//if (!(get_ceiling(line, map) == 1))
			//	return (0);
			//printf("C %d %d %d\n", map->floor->r, map->floor->g, map->floor->b);
		}
		else if (ft_strchr(line, '1'))
		{
			printf("1\n");
			if (!(get_map(line, fd, map) == 1))
				return (0);
		}
		printf("gnl %d\n", len);
	}*/
	printf("gnl %d\n", len);
	return (0);
}
