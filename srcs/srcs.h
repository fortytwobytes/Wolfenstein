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

# define SPEED			5

typedef struct s_player		t_player;
typedef struct s_coor		t_coor;
typedef struct s_mlx		t_mlx;
typedef struct s_var		t_var;
typedef struct s_map_data	t_map_data;

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

struct s_var
{
	t_mlx		mlx;
	t_player	player;
};

struct map_data
{
	int	NO:1;
	int	SO:1;
	int	WE:1;
	int	EA:1;
	int	F:1;
	int	C:1;
};



bool	is_texture_valid(void *mlx, char *path);
bool	is_filename_valid(char *filename);
void    parse_map(char *path);

#endif // !SRCS_H

