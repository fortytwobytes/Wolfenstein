/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relkabou <relkabou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 17:09:19 by onouakch          #+#    #+#             */
/*   Updated: 2023/05/04 17:19:28 by relkabou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <math.h>
#include <time.h>
#include "includes/srcs.h"
#include "lib/MLX42/include/MLX42/MLX42.h"

#define MAP_WIDTH 24
#define MAP_HEIGHT 24
#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 512

#define MINI_MAP_HEIGHT    SCREEN_HEIGHT / 4
#define MINI_MAP_WIDTH    SCREEN_HEIGHT / 4

# define MINI_CUB_SIZE 20

# define RED 0x000000FF


t_vect get_first_player_direction(char direction)
{
	t_vect dir;

	if (direction == 'N')
		dir = (t_vect){0, -1};
	else if (direction == 'S')
		dir = (t_vect){0, 1};
	else if (direction == 'E')
		dir = (t_vect){1, 0};
	else if (direction == 'W')
		dir = (t_vect){-1, 0};
	return (dir);
}

char **dup_worldMap(char **worldMap) {
	char **buffer;
	int i = -1;

	while (worldMap[++i]);
	buffer = malloc(sizeof(char *) * (i + 1));
	i = -1;
	while (worldMap[++i]) {
		buffer[i] = strdup(worldMap[i]);
	}
	buffer[i] = NULL;
	return (buffer);
}

char *worldMap[25] = {
		"111111111111111111111111",
		"100000000000000000000001",
		"100000000000000000000001",
		"1000000000W0000000000001",
		"100000000000000000000001",
		"100000000000000000000001",
		"100000000000000000000001",
		"100000000000000000000001",
		"100000000000000000000001",
		"100000000000000000000001",
		"100000000000000000000001",
		"100000000000000000000001",
		"100000000000000000000001",
		"100000000000000000000001",
		"100000000000000000000001",
		"100000000000000000000001",
		"100000000000000000000001",
		"100000000000000000000001",
		"100000000000000000000001",
		"100000000000000000000001",
		"100000000000000000000001",
		"100000000000000000000001",
		"100000000000000000000001",
		"111111111111111111111111",
		NULL
};

typedef struct s_vect_i {
	int x;
	int y;
} t_vect_i;

typedef struct s_data {
	mlx_t *mlx;
	mlx_image_t *image;
	double pos_x;
	double pos_y;
	double dir_x;
	double dir_y;
	double plane_x;
	double plane_y;
	double c_time;
	double old_time;
	char **dupMap;

} t_data;

typedef struct s_line {
	int line_height;
	int draw_start;
	int draw_end;
} t_line;

typedef struct s_ray {
	double camera_x;
	double ray_dir_x;
	double ray_dir_y;
	double side_dist_x;
	double side_dist_y;
	double perp_wall_dist;
	double delta_dist_x;
	double delta_dist_y;
	int map_x;
	int map_y;
	int step_x;
	int step_y;
	t_line line;
} t_ray;

void	free_split(char **split) {
	int i = -1;
	while (split[++i])
		free(split[i]);
	free(split);
}

void	mlx_draw_cercle(mlx_image_t *image, int x, int y, int size, uint32_t color) {

	int radius = size / 2;
	int cx = x + radius;
	int cy = y + radius;

	for (int i = x; i < x + size; i++) {
		for (int j = y; j < y + size; j++) {
			int dx = i - cx;
			int dy = j - cy;
			if (dx * dx + dy * dy <= radius * radius) {
				mlx_put_pixel(image, i, j, color);
			}
		}
	}

}

void mlx_draw_square(mlx_image_t *image, int x, int y, int size, uint32_t color) {
	int x_end = x + size;
	int y_end = y + size;

	int j = y;

	while (x < x_end) {
		y = j;
		while (y < y_end) {
			mlx_put_pixel(image, x, y, color);
			y++;
		}
		x++;
	}
}

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a) {
	return (r << 24 | g << 16 | b << 8 | a);
}

t_vect_i get_player_xy_position(char **realMap) {
	int x = -1;
	while (realMap[++x]) {
		int y = -1;
		while (realMap[x][++y]) {
			if (strchr("NEWSP", realMap[x][y]))
				return ((t_vect_i) {x, y});
		}
	}
	fatal("No player found");
	return ((t_vect_i) {-1, -1});
}

char **get_minimap(char **realMap) {
	char **minimap;
	int i = -1;

	t_vect_i player_pos = get_player_xy_position(realMap);

	minimap = malloc(sizeof(char *) * (11 + 1));

	int x = player_pos.x - 5;

	size_t map_width = strlen(realMap[0]);
	size_t map_height = 0;
	while (realMap[map_height])
		map_height++;
	while (++i < 11) {
		int j = -1;
		int y = player_pos.y - 5;
		minimap[i] = malloc(sizeof(char) * (11 + 1));
		bzero(minimap[i], 11 + 1);
		memset(minimap[i], '1', 11);

		while (++j < 11) {
			if (x >= 0 && y >= 0 && x < map_height && y < map_width)
				minimap[i][j] = realMap[x][y];
			y++;
		}
		x++;
	}
	minimap[i] = NULL;
	return (minimap);
}

void	draw_direction_(void *args, char **minimap, int32_t color)
{
	t_data *data = (t_data *)args;
	t_vect_i player_pos = get_player_xy_position(minimap);
	t_vect pos;
	pos.x = player_pos.x * MINI_CUB_SIZE + 8 / 2;
	pos.y = player_pos.y * MINI_CUB_SIZE + 8 / 2;
	draw_line(data->image, pos, (t_vect) {pos.x + data->dir_x * 30, pos.y + data->dir_y * 30}, color);

}

void draw_mini_map(t_data *data, char **miniMap) {
	int i = 0;
	int j = 0;

	int x = 0;
	int y = 0;

	i = 0;
	mlx_draw_square(data->image, 0, 0, 11 * MINI_CUB_SIZE, 0xFFFFFFFF);
	while (miniMap[x]) {
		j = 0;
		y = 0;
		while (miniMap[x][y]) {

			if (miniMap[x][y] == '1')
				mlx_draw_square(data->image, i, j, MINI_CUB_SIZE, 0x000000FF);
			else if (miniMap[x][y] == '0') {
				mlx_draw_square(data->image, i, j, MINI_CUB_SIZE, 0xFFFFFFFF);
			}
			else
				mlx_draw_cercle(data->image, i, j, 8, 0xFF0000FF);
			j += MINI_CUB_SIZE;
			y++;
		}
		i += MINI_CUB_SIZE;
		x++;
	}
	draw_direction_(data, miniMap, 0xFF0000FF);
}



void set_env(mlx_image_t *image) {
	int i;
	int j;

	uint32_t color = ft_pixel(0, 0, 0, 0);
	i = -1;
	while (++i < SCREEN_HEIGHT / 2) {
		j = -1;
		while (++j < SCREEN_WIDTH)
			mlx_put_pixel(image, j, i, 0x87CEEBFF);
	}
	color = ft_pixel(112, 128, 144, 255);
	while (++i < SCREEN_HEIGHT) {
		j = -1;
		while (++j < SCREEN_WIDTH)
			mlx_put_pixel(image, j, i, 0x302e2aff);
	}
}

void vert_line(mlx_image_t *image, int x, int drawStart, int drawEnd) {
//	uint32_t color = ft_pixel(104, 252, 0, 255);
	while (drawStart < drawEnd)
		mlx_put_pixel(image, x, drawStart++, 0xff0000ff);
}

void ft_draw(void *args) {
	t_data *data;
	t_ray ray;
	int hit;
	int side;
	int x;

	data = args;
	memset(data->image->pixels, 0, data->image->width * data->image->height * sizeof(uint32_t));
	set_env(data->image);

	x = -1;
	while (++x < SCREEN_WIDTH) {
		//calculate ray position and direction
		ray.camera_x = 2 * x / (double) SCREEN_WIDTH - 1; //x-coordinate in camera space
		ray.ray_dir_x = data->dir_x + data->plane_x * ray.camera_x;
		ray.ray_dir_y = data->dir_y + data->plane_y * ray.camera_x;
		//which box of the map we're in
		ray.map_x = (int) data->pos_x;
		ray.map_y = (int) data->pos_y;

		//length of ray from one x or y-side to next x or y-side
		ray.delta_dist_x = (ray.ray_dir_x == 0) ? 1e00 : fabs(1 / ray.ray_dir_x);
		ray.delta_dist_y = (ray.ray_dir_y == 0) ? 1e00 : fabs(1 / ray.ray_dir_y);

		if (ray.ray_dir_x < 0) {
			ray.step_x = -1;
			ray.side_dist_x = (data->pos_x - ray.map_x) * ray.delta_dist_x;
		} else {
			ray.step_x = 1;
			ray.side_dist_x = (ray.map_x + 1.0 - data->pos_x) * ray.delta_dist_x;
		}
		if (ray.ray_dir_y < 0) {
			ray.step_y = -1;
			ray.side_dist_y = (data->pos_y - ray.map_y) * ray.delta_dist_y;
		} else {
			ray.step_y = 1;
			ray.side_dist_y = (ray.map_y + 1.0 - data->pos_y) * ray.delta_dist_y;
		}
		hit = 0; //was there a wall hit?
		while (hit == 0) {
			//jump to next map square, either in x-direction, or in y-direction
			if (ray.side_dist_x < ray.side_dist_y) {
				ray.side_dist_x += ray.delta_dist_x;
				ray.map_x += ray.step_x;
				side = 0;
			} else {
				ray.side_dist_y += ray.delta_dist_y;
				ray.map_y += ray.step_y;
				side = 1;
			}
			//Check if ray has hit a wall
			if (worldMap[ray.map_x][ray.map_y] > '0') hit = 1;
		}
		ray.perp_wall_dist = (ray.side_dist_y - ray.delta_dist_y);
		if (side == 0)
			ray.perp_wall_dist = (ray.side_dist_x - ray.delta_dist_x);
		ray.line.line_height = (int) (SCREEN_HEIGHT / ray.perp_wall_dist);

		//calculate lowest and highest pixel to fill in current stripe
		ray.line.draw_start = -ray.line.line_height / 2 + SCREEN_HEIGHT / 2;
		if (ray.line.draw_start < 0)
			ray.line.draw_start = 0;
		ray.line.draw_end = ray.line.line_height / 2 + SCREEN_HEIGHT / 2;
		if (ray.line.draw_end >= SCREEN_HEIGHT)
			ray.line.draw_end = SCREEN_HEIGHT - 1;
		vert_line(data->image, x, ray.line.draw_start, ray.line.draw_end);
	}
	t_vect_i p = get_player_xy_position(data->dupMap);
//	putchar(data->dupMap[p.x][p.y]);
	data->dupMap[p.x][p.y] = '0';
	data->dupMap[(int) data->pos_x][(int) data->pos_y] = 'P';
	char **minimap = get_minimap(data->dupMap);
	draw_mini_map(data, minimap);
	free_split(minimap);
}

void ft_hook(void *args) {
	t_data *data;

	data = args;

	data->old_time = data->c_time;
	data->c_time = clock();
	double frame_time = (data->c_time - data->old_time) / 500000;
	//speed modifiers
	double move_speed = frame_time * 5.0; //the constant value is in squares/second
	double rot_speed = frame_time * 3.0; //the constant value is in radians/second

	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
	if (mlx_is_key_down(data->mlx, MLX_KEY_W)) {
		if (worldMap[(int) (data->pos_x + data->dir_x * move_speed)][(int) (data->pos_y)] == '0')
			data->pos_x += data->dir_x * move_speed;
		if (worldMap[(int) (data->pos_x)][(int) (data->pos_y + data->dir_y * move_speed)] == '0')
			data->pos_y += data->dir_y * move_speed;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_S)) {
		if (worldMap[(int) (data->pos_x - data->dir_x * move_speed)][(int) (data->pos_y)] == '0')
			data->pos_x -= data->dir_x * move_speed;
		if (worldMap[(int) (data->pos_x)][(int) (data->pos_y - data->dir_y * move_speed)] == '0')
			data->pos_y -= data->dir_y * move_speed;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_A)) {
		double new_x = data->pos_x - data->plane_x * move_speed;
		double new_y = data->pos_y - data->plane_y * move_speed;
		if (worldMap[(int) new_x][(int) data->pos_y] == '0') {
			data->pos_x = new_x;
		}
		if (worldMap[(int) data->pos_x][(int) new_y] == '0') {
			data->pos_y = new_y;
		}
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_D)) {
		double new_x = data->pos_x + data->plane_x * move_speed;
		double new_y = data->pos_y + data->plane_y * move_speed;
		if (worldMap[(int) new_x][(int) data->pos_y] == '0') {
			data->pos_x = new_x;
		}
		if (worldMap[(int) data->pos_x][(int) new_y] == '0') {
			data->pos_y = new_y;
		}
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT)) {
		//both camera direction and camera plane must be rotated
		double old_dir_x = data->dir_x;
		data->dir_x = data->dir_x * cos(rot_speed) - data->dir_y * sin(rot_speed);
		data->dir_y = old_dir_x * sin(rot_speed) + data->dir_y * cos(rot_speed);
		double old_plane_x = data->plane_x;
		data->plane_x = data->plane_x * cos(rot_speed) - data->plane_y * sin(rot_speed);
		data->plane_y = old_plane_x * sin(rot_speed) + data->plane_y * cos(rot_speed);
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT)) {
		double old_dir_x = data->dir_x;
		data->dir_x = data->dir_x * cos(-rot_speed) - data->dir_y * sin(-rot_speed);
		data->dir_y = old_dir_x * sin(-rot_speed) + data->dir_y * cos(-rot_speed);
		double old_plane_x = data->plane_x;
		data->plane_x = data->plane_x * cos(-rot_speed) - data->plane_y * sin(-rot_speed);
		data->plane_y = old_plane_x * sin(-rot_speed) + data->plane_y * cos(-rot_speed);
	}
	int x, y;
	mlx_get_mouse_pos(data->mlx, &x, &y);
//	printf("x: %d, y: %d\n", x, y);
}

void ft_init(t_data *data) {
	data->pos_x = get_player_xy_position(worldMap).x;
	data->pos_y = get_player_xy_position(worldMap).y;
//	printf("pos_x: %f, pos_y: %f\n", data->pos_x, data->pos_y);
//	printf("%c\n", worldMap[(int)data->pos_x][(int)data->pos_y]);
	data->dir_x = get_first_player_direction(worldMap[(int)data->pos_x][(int)data->pos_y]).x;
	data->dir_y = get_first_player_direction(worldMap[(int)data->pos_x][(int)data->pos_y]).y;
	printf("dir_x: %f, dir_y: %f\n", data->dir_x, data->dir_y);
	data->dir_x = -1.0;
	data->dir_y = 0.0;
	data->plane_x = 0;
	data->plane_y = 0.66;
	data->c_time = 0;
	data->old_time = 0;
	data->mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "MLX42", false);
	data->image = mlx_new_image(data->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	mlx_image_to_window(data->mlx, data->image, 0, 0);
}

// gcc main.c MLX42/build/libmlx42.a -Iinclude -lglfw -L"/Users/$USER/.brew/opt/glfw/lib/"

int32_t main(int32_t argc, const char *argv[]) {
	t_data data;

	ft_init(&data);
	data.dupMap = dup_worldMap(worldMap);

	mlx_loop_hook(data.mlx, ft_draw, &data);
	mlx_loop_hook(data.mlx, ft_hook, &data);

	mlx_loop(data.mlx);
	free_split(data.dupMap);
//	mlx_terminate(data.mlx);
	return (EXIT_SUCCESS);
}
