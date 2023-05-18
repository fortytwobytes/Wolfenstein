/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relkabou <relkabou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 01:36:13 by relkabou          #+#    #+#             */
/*   Updated: 2023/05/17 22:31:53y relkabou         ###   ########.fr       */
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
	move_speed = frame_time * MOVE_SPEED;
	rot_speed = frame_time * ROTATE_SPEED;
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
	t_var	*var;
	int		side;
	int		x;

	var = args;
	ft_memset(var->image->pixels, 0, var->image->width * var->image->height
			* sizeof(uint32_t));
	draw_floor_ceil(var);
	x = -1;
	while (++x < SCREEN_WIDTH)
	{
		resetting_ray(var, &var->ray, x);
		set_step_and_side_distances(var, &var->ray);
		cast_ray_till_wall(var, &var->ray, &side);
		calculate_line_properties(&var->ray, side);
		draw_vert_line(var, x, (t_vect_i) {var->ray.line.draw_start, var->ray.line.draw_end}, side);
	}
	draw_mini_map(var, get_small_map(var));
}
