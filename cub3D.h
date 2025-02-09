#include <mlx.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <math.h>
#include <stdio.h>

typedef struct	s_color
{
	int			r;
	int			g;
	int			b;
}				t_color;

typedef struct	s_map
{
	int			resolution_x;//
	int			resolution_y;//
	char		*no;//
	char		*ea;//
	char		*we;//
	char		*so;//
	char		*sprt;//
	t_color		floor_rgb;//
	t_color		ceiling_rgb;//
	int			x;//
	int			y;//
	int			**map;
}				t_map;

typedef struct	s_img
{
	void		*id;//
	int			*addr;//
	int			endian;//
	int			bpp;//
	int			size_line;//
}				t_img;

typedef struct	s_ray
{
	double		camera_x;//
	double		dirx;//
	double		diry;//
	int			mapx;//
	int			mapy;//
	double		sidedistx;//
	double		sidedisty;//
	double		deltadistx;//
	double		deltadisty;//
	double		perpWallDist;//
	int			stepx;//
	int			stepy;//
	int			hit;//
	double		wallhit_x;
	int			side;//
	int			lineheight;//
	int			drawstart;//
	int			drawend;//
}				t_ray;

# define A_KEY 0
# define W_KEY 13
# define S_KEY 1
# define D_KEY 2
# define LEFT_KEY 123
# define RIGHT_KEY 124
# define ESC_KEY 53

typedef struct	s_key
{
				int a;//
				int w;//
				int s;//
				int d;//
				int left;//
				int right;//
}				t_key;

typedef struct	s_camera
{
	double		dir_x;//
	double		dir_y;//
	double		plane_x;//
	double		plane_y;//
}				t_camera;

typedef struct	s_texture
{
	void		*id;//
	int			width;//
	int			height;//
	int			*addr;//
	int			endian;//
	int			bpp;//
	int			size_line;//
	char		*path;
}				t_texture;

typedef struct	s_var
{
	void		*mlx;//
	void		*win;//
	double		pos_x;//
	double		pos_y;//
	t_camera	camera;
	t_ray		ray;
	t_map		file;
	t_img		img;
	t_key		key;
	t_texture	texture;
}				t_var;

t_map			read_map(char *file_name, t_var *var, int fd);
void			fill_map(char *line, int **map, int x);
int				**create_map(char *file_name, int x, int y);
t_camera		check_coord(char coord, t_map *map, int x, t_var *var);

void			render(t_var *var);

void			get_side_dist(int x, t_var *var);
void			get_hit(t_var *var);
void			get_wall(t_var *var);
void			get_wall_hit(t_var *var);
void			print_column(t_var *var, int x, int texture_x);
char			*select_texture(t_var *var);

void			remove_space(char *line, int *it);
int				ft_strcmp(const char *s1, const char *s2);
size_t			ft_strlen(const char *s);
char			*ft_strnstr(const char *haystack, const char *needle, size_t len);
void			ft_bzero(void *s, size_t n);
int				ft_isdigit(int c);
int				ft_isalpha(int c);
void			*ft_memcpy(void *dst, const void *src, size_t n);
char			*ft_strdup(const char *s1);
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
int				ft_strchr(char *s, char c);
int				get_next_line(int fd, char **line);

void			vertical_movement(t_var *var, double movement_speed, double dirX,
				double dirY);
void			horizontal_movement(t_var *var, double movement_speed, double planeX,
				double planeY);
void			rotation(t_var *var, double rotation_speed);

int				key_pressed(int key, t_var *var);
int				key_released(int key, t_var *var);
int				move_player(t_var *var);
