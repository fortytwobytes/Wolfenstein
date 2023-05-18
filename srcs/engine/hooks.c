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

	var = param;
	if (mlx_is_key_down(var->mlx, MLX_KEY_ESCAPE))
		end_game(var);
	if (mlx_is_key_down(var->mlx, MLX_KEY_W))
		move_forward(var, MOVE_SPEED);
	if (mlx_is_key_down(var->mlx, MLX_KEY_S))
		move_backward(var, MOVE_SPEED);
	if (mlx_is_key_down(var->mlx, MLX_KEY_A))
		move_left(var, MOVE_SPEED);
	if (mlx_is_key_down(var->mlx, MLX_KEY_D))
		move_right(var, MOVE_SPEED);
	if (mlx_is_key_down(var->mlx, MLX_KEY_LEFT))
		change_to_left(var, ROTATE_SPEED);
	if (mlx_is_key_down(var->mlx, MLX_KEY_RIGHT))
		change_to_right(var, ROTATE_SPEED);
	mouse_move(var);
}

void	draw_hook(void *args)
{
	t_var	*var;
	int		x;

	var = args;
	ft_memset(var->image->pixels, 0, var->image->width * var->image->height
			* sizeof(uint32_t));
	x = -1;
	while (++x < SCREEN_WIDTH)
	{
		resetting_ray(var, &var->ray, x);
		set_step_and_side_distances(var, &var->ray);
		cast_ray_till_wall(var, &var->ray, &var->texture.side);
		calculate_line_properties(&var->ray, var->texture.side);
		set_texture_params(var);
		fill_texture_buffer(var, x, var->ray.line.draw_start,
				var->ray.line.draw_end);
	}
	draw_3d_scene(var);
	draw_mini_map(var, get_small_map(var));
}
