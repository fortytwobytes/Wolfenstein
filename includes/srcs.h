#ifndef SRCS_H
# define SRCS_H

# include "libc.h"
# include "../lib/MLX42/include/MLX42/MLX42.h"
# include <math.h>

# define PI 3.14L

# define CUBE_SIZE 32
# define MAP_MAX_HEIGHT	128
# define MAP_MAX_WIDTH 64
# define MAP_MIN_HEIGHT 4
# define MAP_MIN_WIDTH 4
# define PLAYER_SIZE 8
# define WIN_HEIGHT 512
# define WIN_WIDTH 1024

# define SPEED 5
# define ROTATE_SPEED 0.1

# define SPACES " \t\n"

# define NBROF_ELEMENTS 6

typedef struct s_player	t_player;
typedef struct s_coor	t_coor;
typedef struct s_var	t_var;
typedef struct s_map	t_map;

struct					s_coor
{
	float				x;
	float				y;
};

struct					s_player
{
	t_coor				position;
	t_coor				direction;
	float				angle;
	char				first_view;
};

struct					s_map
{
	char				*no_path;
	char				*so_path;
	char				*we_path;
	char				*ea_path;
	int					*f_color;
	int					*c_color;
	int					max_height;
	int					max_width;
	int		 			cub_size;
	char				**map;
	char				*first_map_line;
	char				*last_map_line;
};

struct					s_var
{
	mlx_t				*mlx;
	mlx_image_t			*img;
	mlx_image_t 		*map_img;
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
char					*get_texture(t_var *var, char *path);

/************** parse_map.c *********************/
int						ft_check_map(t_var *var);

/************** parsing.c ***********************/
void					parsing(t_var *var, char *map_file);

#endif // !SRCS_H
