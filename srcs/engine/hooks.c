/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relkabou <relkabou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 01:36:13 by relkabou          #+#    #+#             */
/*   Updated: 2023/05/07 01:36:13 by relkabou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/srcs.h"

void	move_hook(void *param)
{
	t_var	*var;
	double	frame_time;
	double	move_speed;
	double	rot_speed;

	var = param;
	var->old_time = var->c_time;
	var->c_time = (double)clock();
	frame_time = (var->c_time - var->old_time) / 500000;
	move_speed = frame_time * 5.0;
	rot_speed = frame_time * 3.0;
	if (mlx_is_key_down(var->mlx, MLX_KEY_ESCAPE))
		end_game(var);
	if (mlx_is_key_down(var->mlx, MLX_KEY_W))
		move_forward(var, move_speed);
	if (mlx_is_key_down(var->mlx, MLX_KEY_S))
		move_backward(var, move_speed);
	if (mlx_is_key_down(var->mlx, MLX_KEY_A))
		move_left(var, move_speed);
	if (mlx_is_key_down(var->mlx, MLX_KEY_D))
		move_right(var, move_speed);
	if (mlx_is_key_down(var->mlx, MLX_KEY_LEFT))
		change_to_left(var, rot_speed);
	if (mlx_is_key_down(var->mlx, MLX_KEY_RIGHT))
		change_to_right(var, rot_speed);
	mouse_move(var);
}

void	draw_hook(void *args)
{
	t_var		*var;
	t_ray		ray;
	int			hit;
	int			side;
	int			x;
	t_vect_i	p;
	char		**minimap;

	var = args;
	ft_memset(var->image->pixels, 0, var->image->width * var->image->height
			* sizeof(uint32_t));
	draw_floor_ceil(var);
	x = -1;
	while (++x < SCREEN_WIDTH)
	{
		ray.camera_x = 2 * x / (double)SCREEN_WIDTH - 1;
		ray.ray_dir_x = var->dir.x + var->plane.x * ray.camera_x;
		ray.ray_dir_y = var->dir.y + var->plane.y * ray.camera_x;
		ray.map_x = (int)var->pos.x;
		ray.map_y = (int)var->pos.y;
		ray.delta_dist_x = (ray.ray_dir_x == 0) ? 1e00 : fabs(1
				/ ray.ray_dir_x);
		ray.delta_dist_y = (ray.ray_dir_y == 0) ? 1e00 : fabs(1
				/ ray.ray_dir_y);
		if (ray.ray_dir_x < 0)
		{
			ray.step_x = -1;
			ray.side_dist_x = (var->pos.x - ray.map_x) * ray.delta_dist_x;
		}
		else
		{
			ray.step_x = 1;
			ray.side_dist_x = (ray.map_x + 1.0 - var->pos.x) * ray.delta_dist_x;
		}
		if (ray.ray_dir_y < 0)
		{
			ray.step_y = -1;
			ray.side_dist_y = (var->pos.y - ray.map_y) * ray.delta_dist_y;
		}
		else
		{
			ray.step_y = 1;
			ray.side_dist_y = (ray.map_y + 1.0 - var->pos.y) * ray.delta_dist_y;
		}
		hit = 0;
		while (hit == 0)
		{
			if (ray.side_dist_x < ray.side_dist_y)
			{
				ray.side_dist_x += ray.delta_dist_x;
				ray.map_x += ray.step_x;
				side = 0;
			}
			else
			{
				ray.side_dist_y += ray.delta_dist_y;
				ray.map_y += ray.step_y;
				side = 1;
			}
			if (var->map.map[ray.map_x][ray.map_y] == '1')
				hit = 1;
		}
		ray.perp_wall_dist = (ray.side_dist_y - ray.delta_dist_y);
		if (side == 0)
			ray.perp_wall_dist = (ray.side_dist_x - ray.delta_dist_x);
		ray.line.line_height = (int)(SCREEN_HEIGHT / ray.perp_wall_dist);
		ray.line.draw_start = -ray.line.line_height / 2 + SCREEN_HEIGHT / 2;
		if (ray.line.draw_start < 0)
			ray.line.draw_start = 0;
		ray.line.draw_end = ray.line.line_height / 2 + SCREEN_HEIGHT / 2;
		if (ray.line.draw_end >= SCREEN_HEIGHT)
			ray.line.draw_end = SCREEN_HEIGHT - 1;
		draw_vert_line(var->image, x, ray.line.draw_start, ray.line.draw_end);
	}
	p = get_player_xy_position(var->map.map);
	var->map.map[p.x][p.y] = '0';
	var->map.map[(int)var->pos.x][(int)var->pos.y] = 'P';
	minimap = get_minimap(var->map.map);
	draw_mini_map(var, minimap);
	free_split(minimap);
}
