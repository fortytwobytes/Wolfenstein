#ifndef SRCS_H
# define SRCS_H

# include <mlx.h>
# include "../libc/libc.h"

# define WIN_HEIGHT 	1024	// or 512
# define WIN_WIDTH		2048	// or 1024
# define CUBE_SIZE		64		// or 64

# define LEFT			0		// a
# define UP				13		// w
# define DOWN			1		// s
# define RIGHT			2		// d
# define LEFT_ARROW		123		// <-
# define RIGHT_ARROW	124		// ->
# define ESCAPE			53		// esc
# define CLOSE			17		// the close button

# define OK				0
# define KO				1
# define ERROR			-1

# define COMPASS		0
# define COLOR			1

# define SPEED			5

# define SPACES			" \t\n"

# define NBROF_ELEMENTS	6

typedef struct s_player		t_player;
typedef struct s_coor		t_coor;
typedef struct s_mlx		t_mlx;
typedef struct s_var		t_var;
typedef struct s_map		t_map;

struct s_coor
{
	float	x;
	float	y;
};

// FOV: field of view
struct s_player {
	t_coor	position;
	t_coor	direction;
	float	angle;
};

struct s_mlx
{
	void	*mlx;
	void	*win;
};

struct s_map
{
	char	*NO_path;
	char	*SO_path;
	char	*WE_path;
	char	*EA_path;
	int		*F_color;
	int		*C_color;
	int		max_height;
	int		max_width;
	char	**map;
	char	*first_map_line;
};

struct s_var
{
	t_mlx     mlx;
	t_player	player;
  t_map     map;
};



// void	is_texture_valid(void *mlx, char *path);
// bool	is_filename_valid(char *filename);
// // void    parse_map(int fd, char *path);
// bool	is_all_spaces(char *line);
// void	parse_cub_file(t_var *var, char *path);


// /* ** parsing.c ** */
// bool	is_all_num(char **elements);

// /* ** parsing_utils.c ** */
// void	skip_blank_lines(int fd);
// bool	is_all_spaces(char *line);
// void	skip_till_map(int fd, char *first_map_line);
// int		*get_rgb(char *rgb);

// /* ** parsing_elements.c ** */
// void	parse_elements(int fd, t_var *var);

// /* ** parsing_map.c ** */
// void    parse_map(int fd, t_map *map);
// void    get_map_dimentions(int fd, t_map *map);

void	parsing(t_var	*var, char *map_file);

#endif // !SRCS_H

