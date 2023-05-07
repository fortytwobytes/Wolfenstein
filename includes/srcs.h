/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   srcs.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relkabou <relkabou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 17:52:56 by relkabou          #+#    #+#             */
/*   Updated: 2023/05/07 00:49:34 by relkabou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# define SCREEN_WIDTH 1024
# define SCREEN_HEIGHT 512

# define MINI_CUB_SIZE 20

// COLORS
# define BLACK 0x000000FFL
# define RED 0xFF0000FFL
# define WHITE 0xFFFFFFFFL
# define GREEN 0x00FF00FFL

// GAME
# define SPEED 5
# define ROTATE_SPEED M_PI / 48.0f
# define DIRECTION_LEN 50

// MISC
# define SPACES " \t\n"
# define NBROF_ELEMENTS 6
# define PI_2 6.283185307179586
# define FOV 60

typedef unsigned int	uint;
typedef unsigned short	ushort;

typedef struct s_player	t_player;
typedef struct s_vect_f	t_vect_f;
typedef struct s_vect_i	t_vect_i;
typedef struct s_var	t_var;
typedef struct s_map	t_map;
typedef struct s_ray	t_ray;
typedef struct s_line	t_line;

struct					s_vect_i
{
	int					x;
	int					y;
};

struct					s_vect_f
{
	double				x;
	double				y;
};

// (x_pixel, y_pixel) are pointers to the location of the player
// for moving instances you can just differentiate the pointers
struct					s_player
{
	t_vect_f			first_pos;
	t_vect_f			direction;
	int					*x_pixel;
	int					*y_pixel;
	int					x_map;
	int					y_map;
	t_vect_f			next_pos;
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
	int					height;
	int					width;
	char				**map;
	char				*first_map_line;
};

struct					s_var
{
	mlx_t				*mlx;
	mlx_image_t			*image;
	t_player			player;
	t_map				map;
	t_vect_f			pos;
	t_vect_f			dir;
	t_vect_f			plane;
	double				c_time;
	double				old_time;
	char				**dupMap;
};

struct					s_line
{
	int					line_height;
	int					draw_start;
	int					draw_end;
};

struct					s_ray
{
	double				camera_x;
	double				ray_dir_x;
	double				ray_dir_y;
	double				side_dist_x;
	double				side_dist_y;
	double				perp_wall_dist;
	double				delta_dist_x;
	double				delta_dist_y;
	int					map_x;
	int					map_y;
	int					step_x;
	int					step_y;
	t_line				line;
};

void					move_hook(void *param);
void					draw_hook(void *args);

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
void					parsing(t_var *var, const char *cubFilename);

/* ***** inits.c ***** */
void					init_window(t_var *var);
void					init_images(t_var *var);

// drawing.c
void					draw_player(void *params);
void					draw_map(void *params);

// ---------- syscalls.c ---------- //
int						ft_open(const char *pathname);

// ---------- srcs/engine/utils ---------- //
void					draw_line(mlx_image_t *image, t_vect_f p1, t_vect_f p2,
							uint color);

// ---------- srcs/engine/ ---------- //
void					draw_mini_map(t_var *data, char **miniMap);
// view.c
void					change_to_left(t_var *var, double rotSpeed);
void					change_to_right(t_var *var, double rotSpeed);
// move.c
void					move_forward(t_var *var, double moveSpeed);
void					move_backward(t_var *var, double moveSpeed);
void					move_left(t_var *var, double moveSpeed);
void					move_right(t_var *var, double moveSpeed);

// ---------- srcs/utils ---------- //
// drawing.c
void					draw_direction(void *args, char **minimap,
							uint32_t color);
void					mlx_draw_circle(mlx_image_t *image, int x, int y,
							int size, uint32_t color);
void					mlx_draw_square(mlx_image_t *image, int x, int y,
							int size, uint32_t color);
void					draw_vert_line(mlx_image_t *image, int x, int drawStart,
							int drawEnd);
void					draw_floor_ceil(t_var *var);
// helpers.c
void					free_split(char **split);
t_vect_i				get_player_xy_position(char **realMap);
t_vect_f				get_first_player_direction(char direction);

//later
char					**get_minimap(char **realMap);
void					end_game(t_var *var);

#endif // !SRCS_H
