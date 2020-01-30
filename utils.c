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
