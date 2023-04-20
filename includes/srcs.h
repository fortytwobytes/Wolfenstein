#ifndef SRCS_H
# define SRCS_H

# include "libc.h"
# include "../lib/MLX42/include/MLX42/MLX42.h"
# include <math.h>

// WINDOW
# define CUBE_SIZE 64
# define PLAYER_SIZE 8
# define WIN_HEIGHT 512
# define WIN_WIDTH 1024

// COLORS
# define RED	0xFF0000FFL
# define WHITE	0xFFFFFFFFL
# define BLACK	0x000000FFL

// FGAmE
# define SPEED 5
# define ROTATE_SPEED 0.1

// MISC
# define SPACES " \t\n"
# define NBROF_ELEMENTS 6

typedef struct s_player	t_player;
typedef struct s_coor	t_coor;
typedef struct s_var	t_var;
typedef struct s_map	t_map;
typedef struct s_coor_f	t_coor_f;

struct					s_coor
{
    int                 x;
    int                 y;
};

struct s_coor_f {
	double x;
	double y;
};

struct					s_player
{
	mlx_image_t 		*img;
	t_coor_f			direction;
	double				angle;
	char				first_view;
    t_coor              pos;
};

struct					s_map
{
	mlx_image_t 		*no_image;
	mlx_image_t 		*so_image;
	mlx_image_t 		*we_image;
	mlx_image_t 		*ea_image;
	u_int32_t 			f_color;
	u_int32_t 			c_color;
	int					max_height;
	int					max_width;
	char				**map;
	char				*first_map_line;
};

struct					s_var
{
	mlx_t				*mlx;
	mlx_image_t			*scene3d;
	mlx_image_t 		*minimap;
	t_player			player;
	t_map				map;
};

void					hooks(void *param);

/************* parse_elements.c *****************/
char					*readline_skipping_spaces(int fd);
void					fill_map_struct(t_var *var, char *element, char *arg);

/************** parse_utils.c *******************/
void					get_map_dimentions(int fd, t_map *map);
void					skip_till_first_map_line(int fd, t_map *map);
mlx_image_t				*get_texture(t_var *var, char *path);
u_int32_t				get_color(int *rgb);

/************** parse_map.c *********************/
int						ft_check_map(t_var *var);

/************** parsing.c ***********************/
void					parsing(t_var *var, char *map_file);

/* ***** inits.c ***** */
void                    init_window(t_var *var);
void					init_images(t_var *var);

// drawing.c
void draw_player(void *params);
void draw_map(void *params);

double	getAngle(double angle);


#endif // !SRCS_H
