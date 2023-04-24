#ifndef SRCS_H
# define SRCS_H

# include "../lib/MLX42/include/MLX42/MLX42.h"
# include "libc.h"
# include <math.h>

// WINDOW
# define CUBE_SIZE 64
# define PLAYER_SIZE 8
# define WIN_HEIGHT 512
# define WIN_WIDTH 1024

// COLORS
# define BLACK 0x000000FFL
# define RED 0xFF0000FFL
# define WHITE 0xFFFFFFFFL

// GAME
# define SPEED 5
# define ROTATE_SPEED M_PI / 48.0f

// MISC
# define SPACES " \t\n"
# define NBROF_ELEMENTS 6
# define PI_2 6.283185307179586
# define FOV 60

typedef struct s_player	t_player;
typedef struct s_vect	t_vect;
typedef struct s_var	t_var;
typedef struct s_map	t_map;
typedef struct s_rect	t_rect;

struct					s_vect
{
	double				x;
	double				y;
};

struct					s_rect
{
	t_vect				coor;
	uint32_t			width;
	uint32_t			height;
};

struct					s_player
{
	t_vect				first_pos;
	t_vect				direction;
	int					*x_pos;
	int 				*y_pos;
	double				angle;
	char				first_view;
	mlx_image_t			*img;
};

struct					s_map
{
	mlx_image_t			*no_image;
	mlx_image_t			*so_image;
	mlx_image_t			*we_image;
	mlx_image_t			*ea_image;
	long				f_color;
	long				c_color;
	int					max_height;
	int					max_width;
	char				**map;
	char				*first_map_line;
};

struct					s_var
{
	mlx_t				*mlx;
	mlx_image_t			*scene3d;
	mlx_image_t			*minimap;
	t_player			player;
	t_map				map;
};

void					hooks(void *param);

/************* parse_elements.c *****************/
char					*readline_skipping_spaces(int fd);
void					fill_map_struct(t_var *var, char *element, char *arg);

/************** parse_utils.c *******************/
void					get_map_dimension(int fd, t_map *map);
void					skip_till_first_map_line(int fd, t_map *map);
mlx_image_t				*get_texture(t_var *var, char *path);
u_int32_t				get_color(int *rgb);

/************** parse_map.c *********************/
int						ft_check_map(t_var *var);

/************** parsing.c ***********************/
void					parsing(t_var *var, char *cubFilename);

/* ***** inits.c ***** */
void					init_window(t_var *var);
void					init_images(t_var *var);

// drawing.c
void					draw_player(void *params);
void					draw_map(void *params);

double					get_angle(double angle);

// norm
int						ft_open(const char *pathname);

void                    move_up(t_map map, t_player *p);
void                    move_down(t_map map, t_player *p);
void                    move_left(t_map map, t_player *p);
void                    move_right(t_map map, t_player *p);


#endif // !SRCS_H
