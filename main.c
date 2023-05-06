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

#include "includes/srcs.h"
#include <time.h>
#include "lib/MLX42/include/MLX42/MLX42.h"

void	end_game(t_var *var) {
	free_split(var->map.map);
	mlx_delete_image(var->mlx, var->image);
	mlx_close_window(var->mlx);
	exit(0);
}

char **dup_world_map(char **worldMap) {
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





void draw_hook(void *args) {
	t_var *var;
	t_ray ray;
	int hit;
	int side;
	int x;

	var = args;
	memset(var->image->pixels, 0, var->image->width * var->image->height * sizeof(uint32_t));
	draw_floor_ceil(var->image);

	x = -1;
	while (++x < SCREEN_WIDTH) {
		//calculate ray position and direction
		ray.camera_x = 2 * x / (double) SCREEN_WIDTH - 1; //x-coordinate in camera space
		ray.ray_dir_x = var->dir.x + var->plane.x * ray.camera_x;
		ray.ray_dir_y = var->dir.y + var->plane.y * ray.camera_x;
		//which box of the map we're in
		ray.map_x = (int) var->pos.x;
		ray.map_y = (int) var->pos.y;

		//length of ray from one x or y-side to next x or y-side
		ray.delta_dist_x = (ray.ray_dir_x == 0) ? 1e00 : fabs(1 / ray.ray_dir_x);
		ray.delta_dist_y = (ray.ray_dir_y == 0) ? 1e00 : fabs(1 / ray.ray_dir_y);

		if (ray.ray_dir_x < 0) {
			ray.step_x = -1;
			ray.side_dist_x = (var->pos.x - ray.map_x) * ray.delta_dist_x;
		} else {
			ray.step_x = 1;
			ray.side_dist_x = (ray.map_x + 1.0 - var->pos.x) * ray.delta_dist_x;
		}
		if (ray.ray_dir_y < 0) {
			ray.step_y = -1;
			ray.side_dist_y = (var->pos.y - ray.map_y) * ray.delta_dist_y;
		} else {
			ray.step_y = 1;
			ray.side_dist_y = (ray.map_y + 1.0 - var->pos.y) * ray.delta_dist_y;
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
		draw_vert_line(var->image, x, ray.line.draw_start, ray.line.draw_end);
	}
	t_vect_i p = get_player_xy_position(var->dupMap);
	var->dupMap[p.x][p.y] = '0';
	var->dupMap[(int) var->pos.x][(int) var->pos.y] = 'P';

	char **minimap = get_minimap(var->dupMap);
	draw_mini_map(var, minimap);
	free_split(minimap);
}

void move_hook(void *args) {
	t_var *var;

	var = args;

	var->old_time = var->c_time;
	var->c_time = (double) clock();
	double frame_time = (var->c_time - var->old_time) / 500000;
	//speed modifiers
	double move_speed = frame_time * 5.0; //the constant value is in squares/second
	double rot_speed = frame_time * 3.0; //the constant value is in radians/second

	if (mlx_is_key_down(var->mlx, MLX_KEY_ESCAPE)) {
		// end game
		end_game(var);
	}
	if (mlx_is_key_down(var->mlx, MLX_KEY_W)) {
		if (worldMap[(int) (var->pos.x + var->dir.x * move_speed)][(int) (var->pos.y)] == '0')
			var->pos.x += var->dir.x * move_speed;
		if (worldMap[(int) (var->pos.x)][(int) (var->pos.y + var->dir.y * move_speed)] == '0')
			var->pos.y += var->dir.y * move_speed;
	}
	if (mlx_is_key_down(var->mlx, MLX_KEY_S)) {
		if (worldMap[(int) (var->pos.x - var->dir.x * move_speed)][(int) (var->pos.y)] == '0')
			var->pos.x -= var->dir.x * move_speed;
		if (worldMap[(int) (var->pos.x)][(int) (var->pos.y - var->dir.y * move_speed)] == '0')
			var->pos.y -= var->dir.y * move_speed;
	}
	if (mlx_is_key_down(var->mlx, MLX_KEY_A)) {
		double new_x = var->pos.x - var->plane.x * move_speed;
		double new_y = var->pos.y - var->plane.y * move_speed;
		if (worldMap[(int) new_x][(int) var->pos.y] == '0') {
			var->pos.x = new_x;
		}
		if (worldMap[(int) var->pos.x][(int) new_y] == '0') {
			var->pos.y = new_y;
		}
	}
	if (mlx_is_key_down(var->mlx, MLX_KEY_D)) {
		double new_x = var->pos.x + var->plane.x * move_speed;
		double new_y = var->pos.y + var->plane.y * move_speed;
		if (worldMap[(int) new_x][(int) var->pos.y] == '0') {
			var->pos.x = new_x;
		}
		if (worldMap[(int) var->pos.x][(int) new_y] == '0') {
			var->pos.y = new_y;
		}
	}
	if (mlx_is_key_down(var->mlx, MLX_KEY_LEFT)) {
		//both camera direction and camera plane must be rotated
		double old_dir_x = var->dir.x;
		var->dir.x = var->dir.x * cos(rot_speed) - var->dir.y * sin(rot_speed);
		var->dir.y = old_dir_x * sin(rot_speed) + var->dir.y * cos(rot_speed);
		double old_plane_x = var->plane.x;
		var->plane.x = var->plane.x * cos(rot_speed) - var->plane.y * sin(rot_speed);
		var->plane.y = old_plane_x * sin(rot_speed) + var->plane.y * cos(rot_speed);
	}
	if (mlx_is_key_down(var->mlx, MLX_KEY_RIGHT)) {
		double old_dir_x = var->dir.x;
		var->dir.x = var->dir.x * cos(-rot_speed) - var->dir.y * sin(-rot_speed);
		var->dir.y = old_dir_x * sin(-rot_speed) + var->dir.y * cos(-rot_speed);
		double old_plane_x = var->plane.x;
		var->plane.x = var->plane.x * cos(-rot_speed) - var->plane.y * sin(-rot_speed);
		var->plane.y = old_plane_x * sin(-rot_speed) + var->plane.y * cos(-rot_speed);
	}
}

void init(t_var *var) {
	var->pos.x = get_player_xy_position(worldMap).x;
	var->pos.y = get_player_xy_position(worldMap).y;
	// we should change this to get the first player direction
//	var->dir.x = get_first_player_direction(worldMap[(int)data->pos.x][(int)data->pos.y]).x;
//	var->dir.y = get_first_player_direction(worldMap[(int)data->pos.x][(int)data->pos.y]).y;
	var->dir.x = -1.0;
	var->dir.y = 0.0;
	var->plane.x = 0;
	var->plane.y = 0.66;
	var->c_time = 0;
	var->old_time = 0;
	var->image = mlx_new_image(var->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	mlx_image_to_window(var->mlx, var->image, 0, 0);
}

int32_t main(int32_t argc, const char *argv[]) {
	t_var var;

	if (argc != 2) {
		fatal("Usage: ./cub3D <map.cub>\n");
	}
	init_window(&var);
	parsing(&var, argv[1]);
	init(&var);

	var.dupMap = dup_world_map(worldMap);

	mlx_loop_hook(var.mlx, move_hook, &var);
	mlx_loop_hook(var.mlx, draw_hook, &var);

	mlx_loop(var.mlx);
	free_split(var.dupMap);
//	mlx_terminate(var.mlx);
	return (EXIT_SUCCESS);
}
