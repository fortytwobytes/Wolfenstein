/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relkabou <relkabou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 00:48:55 by relkabou          #+#    #+#             */
/*   Updated: 2023/05/07 00:48:55 by relkabou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/srcs.h"

void	change_to_left(t_var *var, double rotSpeed)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = var->dir.x;
	var->dir.x = var->dir.x * cos(rotSpeed) - var->dir.y * sin(rotSpeed);
	var->dir.y = old_dir_x * sin(rotSpeed) + var->dir.y * cos(rotSpeed);
	old_plane_x = var->plane.x;
	var->plane.x = var->plane.x * cos(rotSpeed) - var->plane.y * sin(rotSpeed);
	var->plane.y = old_plane_x * sin(rotSpeed) + var->plane.y * cos(rotSpeed);
}

void	change_to_right(t_var *var, double rotSpeed)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = var->dir.x;
	var->dir.x = var->dir.x * cos(-rotSpeed) - var->dir.y * sin(-rotSpeed);
	var->dir.y = old_dir_x * sin(-rotSpeed) + var->dir.y * cos(-rotSpeed);
	old_plane_x = var->plane.x;
	var->plane.x = var->plane.x * cos(-rotSpeed) - var->plane.y
		* sin(-rotSpeed);
	var->plane.y = old_plane_x * sin(-rotSpeed) + var->plane.y * cos(-rotSpeed);
}

void	mouse_move(t_var *var)
{
	double	half_screen;

	half_screen = var->image->width / 2.0;
	mlx_get_mouse_pos(var->mlx, &var->mouse.x, &var->mouse.y);
	if (mlx_is_mouse_down(var->mlx, MLX_MOUSE_BUTTON_LEFT) == false)
		return ;
	if (var->mouse.x < half_screen)
		change_to_left(var, ROTATE_SPEED / 20);
	else if (var->mouse.x > half_screen)
		change_to_right(var, ROTATE_SPEED / 20);
}
