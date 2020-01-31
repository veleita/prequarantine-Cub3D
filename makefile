NAME		= cub3D

CC			= gcc
WFLAGS		= -Werror -Wall -Wextra

INCLUDES	= -l mlx -I /usr/X11/include
FRAMEWORKS	= -framework Appkit -framework OpenGL

SRCS		= main.c render.c utils.c print_world.c raycasting.c

all:		$(NAME)
				./$(NAME)

mlx:
				$(CC) $(WFLAGS) $(INCLUDES) $(FRAMEWORKS) mlx_testing.c && ./a.out

$(NAME): $(SRCS)
				$(CC) $(WFLAGS) $(INCLUDES) $(FRAMEWORKS) $(SRCS) -o $(NAME)

map:
				$(CC) $(WFLAGS) read_map.c -o map
				./map map1basic.cub
#clean:

fclean:
				rm -rf $(NAME)

re: fclean all
