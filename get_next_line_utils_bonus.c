/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzomeno- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 13:14:20 by mzomeno-          #+#    #+#             */
/*   Updated: 2019/12/18 13:14:29 by mzomeno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int		ft_strlen(const char *str)
{
	int cont;

	cont = 0;
	while (*(str++) != '\0')
		cont++;
	return (cont);
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
