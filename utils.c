#include "cub3D.h"

int		ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 || *s2)
	{
		if ((unsigned char)*s1 != (unsigned char)*s2)
			return ((unsigned char)*s1 - (unsigned char)*s2);
		s1++;
		s2++;
	}
	return (0);
}

size_t		ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	const char	*str;
	const char	*set;
	size_t		size;

	if (!*needle)
		return ((char*)haystack);
	while (*haystack && len > 0)
	{
		str = haystack;
		set = needle;
		size = len;
		while (*str == *set && *set && size--)
		{
			str++;
			set++;
		}
		if (*set == '\0')
		haystack++;
		--len;
	}
	return (NULL);
}

void	ft_bzero(void *s, size_t n)
{
	size_t i;

	i = -1;
	while (++i < n)
		((char*)s)[i] = 0;
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
