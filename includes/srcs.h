/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   srcs.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouakch <onouakch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 17:52:56 by relkabou          #+#    #+#             */
/*   Updated: 2023/05/18 20:36:59 by onouakch         ###   ########.fr       */
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

// GAME
# define MOVE_SPEED 0.08f
# define ROTATE_SPEED 0.04f
# define DIRECTION_LEN 50

// MISC
# define SPACES " \t\n"
# define NBROF_ELEMENTS 6

typedef struct s_player		t_player;
typedef struct s_vect_f		t_vect_f;
typedef struct s_vect_i		t_vect_i;
typedef struct s_var		t_var;
typedef struct s_map		t_map;
typedef struct s_ray		t_ray;
typedef struct s_line		t_line;
typedef struct s_idxs		t_idxs;
typedef struct s_minimap	t_minimap;
typedef struct s_texture	t_texture;

struct						s_vect_i
{
	int						x;
	int						y;
};

struct						s_vect_f
{
	double					x;
	double					y;
};

struct						s_idxs
{
	int						i;
	int						j;
};

struct						s_player
{
	t_vect_f				first_pos;
	char					first_view;
};

struct						s_texture
{
	uint32_t				**buffer;
	double					pos;
	int						tex_x;
	int						tex_y;
	int						side;
	double					step;
};

struct						s_minimap
{
	t_vect_i				p;
	t_vect_i				player_pos;
	t_vect_i				map;
	int						i;
	int						j;
	char					**minimap;
};

struct						s_map
{
	mlx_image_t				*no_image;
	mlx_image_t				*so_image;
	mlx_image_t				*we_image;
	mlx_image_t				*ea_image;
	long					f_color;
	long					c_color;
	int						height;
	int						width;
	char					**map;
	char					*first_map_line;
};

struct						s_line
{
	int						line_height;
	int						draw_start;
	int						draw_end;
};

struct						s_ray
{
	double					camera_x;
	double					ray_dir_x;
	double					ray_dir_y;
	double					side_dist_x;
	double					side_dist_y;
	double					perp_wall_dist;
	double					delta_dist_x;
	double					delta_dist_y;
	int						map_x;
	int						map_y;
	int						step_x;
	int						step_y;
	t_line					line;
};

struct						s_var
{
	mlx_t					*mlx;
	mlx_image_t				*image;
	t_player				player;
	t_texture				texture;
	t_map					map;
	t_vect_f				pos;
	t_vect_f				dir;
	t_vect_f				plane;
	t_vect_i				mouse;
	t_ray					ray;
	double					c_time;
	double					old_time;
};

void						move_hook(void *param);
void						draw_hook(void *args);

/************* parse_elements.fix_coor *****************/
char						*readline_skipping_spaces(int fd);
void						fill_map_struct(t_var *var, char *element,
								char *arg);

/************** parse_utils.fix_coor *******************/
void						get_map_dimension(int fd, t_map *map);
void						skip_till_first_map_line(int fd, t_map *map);
mlx_image_t					*get_texture(t_var *var, char *path);
u_int32_t					get_color(int *rgb);

/************** parse_map.fix_coor *********************/
int							ft_check_map(t_var *var);

/************** parsing.fix_coor ***********************/
void						parsing(t_var *var, const char *cubFilename);

/* ***** inits.fix_coor ***** */
void						init_window(t_var *var);
void						init_images(t_var *var);

// drawing.fix_coor
void						draw_player(void *params);
void						draw_map(void *params);

// ---------- sys_calls.fix_coor ---------- //
int							ft_open(const char *pathname);

// ---------- srcs/engine/utils ---------- //
void						draw_line(mlx_image_t *image, t_vect_i p1,
								t_vect_i p2, uint32_t color);

// ---------- srcs/engine/ ---------- //
void						draw_mini_map(t_var *data, char **miniMap);
// view.fix_coor
void						change_to_left(t_var *var, double rotSpeed);
void						change_to_right(t_var *var, double rotSpeed);
// move.fix_coor
void						move_forward(t_var *var, double moveSpeed);
void						move_backward(t_var *var, double moveSpeed);
void						move_left(t_var *var, double moveSpeed);
void						move_right(t_var *var, double moveSpeed);

// ---------- srcs/utils ---------- //
// drawing.fix_coor
void						draw_direction(void *args, char **minimap,
								uint32_t color);
void						draw_circle(mlx_image_t *image, t_vect_i p,
								int size, uint32_t color);
void						draw_square(mlx_image_t *image, t_vect_i p,
								int size, uint32_t color);
void						fill_texture_buffer(t_var *image, int x,
								int drawStart, int drawEnd);
void						draw_floor_ceil(t_var *var);
// helpers.fix_coor
void						free_split(char **split);
t_vect_i					get_player_xy_position(char **realMap);
t_vect_f					get_first_player_direction(t_var *var,
								char direction);

//later
char						**get_minimap(char **realMap);
char						**get_small_map(t_var *var);
void						end_game(t_var *var);

void						mouse_move(t_var *var);

void						init(t_var *var);

// casting.fix_coor
void						resetting_ray(t_var *var, t_ray *ray, int xPixel);
void						set_step_and_side_distances(t_var *var, t_ray *ray);
void						cast_ray_till_wall(t_var *var, t_ray *ray,
								int *side);
void						calculate_line_properties(t_ray *ray, int side);
uint32_t					get_image_color(mlx_image_t *image, t_vect_i p);

void						set_texture_params(t_var *var);
void						set_env(t_var *var);
void						draw_3d_scene(t_var *var);
void						fill_texture_buffer(t_var *var, int x,
								int drawStart, int drawEnd);
t_vect_i					fix_coor(int x, int y, int size);
void						check_cube(t_var *data, char **miniMap, t_idxs idx,
								t_vect_i p);
#endif // !SRCS_H
