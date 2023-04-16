#ifndef SRCS_H
# define SRCS_H

# include "../libc/libc.h"
# include <MLX42/MLX42.h>
# include <math.h>

# define PI 3.14

# define WIN_HEIGHT 1024 // or 512
# define WIN_WIDTH 2048  // or 1024
# define CUBE_SIZE 64    // or 64

# define SPEED 5
# define ROTATE_SPEED 0.1

# define SPACES " \t\n"

# define NBROF_ELEMENTS 6

typedef struct s_player	t_player;
typedef struct s_coor	t_coor;
typedef struct s_mlx	t_mlx;
typedef struct s_var	t_var;
typedef struct s_map	t_map;

struct					s_coor
{
	float				x;
	float				y;
};

// FOV: field of view

struct s_player {
	t_coor	position;
	t_coor	direction;
	float	angle;
	char	first_view;
};

struct					s_mlx
{
	void				*mlx;
	void				*win;
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
	char				**map;
	char				*first_map_line;
  char        *last_map_line;
	// later ******************
	void				*no_img;
	void				*so_img;
	void				*we_img;
	void				*ea_img;
};

struct					s_var
{
	t_mlx				mlx;
	t_player			player;
	t_map				map;
};

void					parsing(t_var *var, char *map_file);
void					hooks(mlx_key_data_t keydata, void *param);
#endif // !SRCS_H
