/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzomeno- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 13:11:32 by mzomeno-          #+#    #+#             */
/*   Updated: 2019/12/18 13:11:42 by mzomeno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

	if (!line || fd < 0 || !(buffer = (char *)malloc(BUFFER_SIZE + 1)))
		return (-1);
	while ((len = read(fd, buffer, BUFFER_SIZE + 1)) > 0)
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
