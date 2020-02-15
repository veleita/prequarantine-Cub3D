#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include "get_next_line.h"

typedef struct			s_map
{
	char				*line;
	struct s_map		*next;
}						t_list;

t_list	*ft_lstnew(char *content)
{
	t_list	*ret;

	if (!(ret = (t_list*)malloc(sizeof(t_list*))))
		return (NULL);
	ret->line = content;
	ret->next = NULL;
	return (ret);
}

t_list	*ft_lstlast(t_list *lst)
{
	if (lst)
		while (lst->next)
			lst = lst->next;
	return (lst);
}

void	ft_lstadd_back(t_list **alst, t_list *newlst)
{
	t_list *lst;

	if (alst && newlst)
	{
		if (!*alst)
			*alst = newlst;
		else
		{
			lst = ft_lstlast(*alst);
			lst->next = newlst;
		}
	}
}

int		charge_map(char *file_name)
{
	int		fd = open(file_name, O_RDONLY);
	char	*line;
	t_list	**map;
	t_list	*newlst;

	if (!(map = malloc(sizeof(10000))))
		return (0);
	while ((get_next_line(fd, &line)) > 0)
	{
		//printf("%s", line);
		newlst = ft_lstnew(line);
		ft_lstadd_back(map, newlst);
		//printf("line %s\n", (*map)->line);
	}
	free(newlst);
	free(map);
	return (0);
}

int main()
{
	charge_map("lab.cub");
	return (0);
}
