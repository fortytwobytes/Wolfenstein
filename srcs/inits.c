/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relkabou <relkabou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 00:51:26 by relkabou          #+#    #+#             */
/*   Updated: 2023/05/07 00:51:26 by relkabou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/srcs.h"

void	init_window(t_var *var)
{
	mlx_set_setting(MLX_STRETCH_IMAGE, false);
	mlx_set_setting(MLX_DECORATED, false);
	var->mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "WolFeinstein 3D", true);
	if (var->mlx == NULL)
	{
		fatal(mlx_strerror(mlx_errno));
	}
	mlx_set_window_limit(var->mlx, WIN_WIDTH, WIN_HEIGHT, WIN_WIDTH,
			WIN_HEIGHT);
}

void init(t_var *var)
{
	var->pos.x = get_player_xy_position(var->map.map).x;
	var->pos.y = get_player_xy_position(var->map.map).y;
	var->dir.x = get_first_player_direction(var->map.map[(int)var->pos.x][(int)var->pos.y]).x;
	var->dir.y = get_first_player_direction(var->map.map[(int)var->pos.x][(int)var->pos.y]).y;
	var->plane.x = 0;
	var->plane.y = 0.66;
	var->c_time = 0;
	var->old_time = 0;
	var->map.map[(int)var->pos.x][(int)var->pos.y] = 'P';
	var->image = mlx_new_image(var->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	mlx_image_to_window(var->mlx, var->image, 0, 0);
}
