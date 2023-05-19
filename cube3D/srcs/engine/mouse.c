/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouakch <onouakch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 17:24:47 by onouakch          #+#    #+#             */
/*   Updated: 2023/05/19 17:24:48 by onouakch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/srcs.h"

void	mouse_move(t_var *var)
{
	double	half_screen;

	half_screen = var->image->width / 2.0;
	mlx_get_mouse_pos(var->mlx, &var->mouse.x, &var->mouse.y);
	if (var->is_mouse_on == false)
	{
		mlx_set_cursor_mode(var->mlx, MLX_MOUSE_NORMAL);
		return ;
	}
	mlx_set_cursor_mode(var->mlx, MLX_MOUSE_HIDDEN);
	if (var->mouse.x < half_screen)
		change_to_left(var, ROTATE_SPEED);
	else if (var->mouse.x > half_screen)
		change_to_right(var, ROTATE_SPEED);
	mlx_set_mouse_pos(var->mlx, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
}

void	switch_mouse_mode(mlx_key_data_t keydata, void *params)
{
	t_var	*var;

	var = (t_var *)params;
	if (keydata.key == MLX_KEY_SPACE && keydata.action == MLX_PRESS)
		var->is_mouse_on = !var->is_mouse_on;
}
