NAME		= cub3D

CC			= gcc
WFLAGS		= -Werror -Wall -Wextra

INCLUDES	= -l mlx -I /usr/X11/include
FRAMEWORKS	= -framework Appkit -framework OpenGL

SRCS		= mlx_testing.c


all:		$(NAME)
				./$(NAME)

$(NAME): $(SRCS)
				$(CC) $(WFLAGS) $(INCLUDES) $(FRAMEWORKS) $(SRCS) -o $(NAME)

#clean:

fclean: $(NAME)
				rm -rf $(NAME)

#re:
