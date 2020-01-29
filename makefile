NAME		= cub3D

CC			= gcc
WFLAGS		= -Werror -Wall -Wextra

INCLUDES	= -l mlx -I /usr/X11/include
FRAMEWORKS	= -framework Appkit -framework OpenGL

SRCS		= print_walls.c


all:		$(NAME)
				./$(NAME)

mlx:
				$(CC) $(WFLAGS) $(INCLUDES) $(FRAMEWORKS) mlx_testing.c && ./a.out

$(NAME): $(SRCS)
				$(CC) $(WFLAGS) $(INCLUDES) $(FRAMEWORKS) $(SRCS) -o $(NAME)

#clean:

fclean:
				rm -rf $(NAME)

re: fclean all
