#include <mlx.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

typedef struct	s_map
{
	int			x_max;
	int			y_max;
	int			map[16][29];
}				t_map;

typedef struct	s_color
{
	int			t;
	int			r;
	int			g;
	int			b;
}				t_color;

typedef struct	s_img
{
	void		*id;//
	int			*addr;//
	int			x;
	int			y;
	int			endian;//
	int			bpp;//
	int			size_line;//
}				t_img;

typedef struct	s_ray
{
	double		cameraX;//
	double		raydirx;//
	double		raydiry;//
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
	int			side;//
	int			lineHeight;//
	int			drawStart;//
	int			drawEnd;//
	t_color		color;
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
	int a;
	int w;
	int s;
	int d;
	int left;
	int right;
}		t_key;

typedef struct	s_var
{
	void		*mlx;//
	void		*win;//
	double		posx;
	double		posy;
	double		dirX;
	double		dirY;
	double		planeX;
	double		planeY;
	int			screenWidth;
	int			screenHeight;
	t_ray		ray;
	t_map		map;
	t_img		img;
	t_key		key;
}				t_var;

void	render(t_var *var);

void	get_side_dist(int x, t_var *var);
void	get_hit(t_var *var, int map[16][29]);
void	get_wall(t_var *var);
void	print_column(t_var *var, int x);

int		ft_strcmp(const char *s1, const char *s2);
size_t	ft_strlen(const char *s);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
void	ft_bzero(void *s, size_t n);

void	vertical_movement(t_var *var, double movement_speed, double dirX,
		double dirY);
void	horizontal_movement(t_var *var, double movement_speed, double planeX,
		double planeY);
void	rotation(t_var *var, double rotation_speed);

int		key_pressed(int key, t_var *var);
int		key_released(int key, t_var *var);
int		move_player(t_var *var);

int		finish();
