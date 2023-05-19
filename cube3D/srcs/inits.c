/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouakch <onouakch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 00:51:26 by relkabou          #+#    #+#             */
/*   Updated: 2023/05/19 17:24:00 by onouakch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/srcs.h"

void	init_window(t_var *var)
{
	mlx_set_setting(MLX_STRETCH_IMAGE, false);
	mlx_set_setting(MLX_DECORATED, true);
	var->mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "WolFeinstein 3D", true);
	if (var->mlx == NULL)
	{
		fatal(mlx_strerror(mlx_errno));
	}
	var->is_mouse_on = true;
	mlx_set_cursor_mode(var->mlx, MLX_MOUSE_HIDDEN);
	mlx_set_window_limit(var->mlx, WIN_WIDTH, WIN_HEIGHT, WIN_WIDTH,
		WIN_HEIGHT);
}

void	init(t_var *var)
{
	int	i;

	i = -1;
	var->pos.x = get_player_xy_position(var->map.map).x;
	var->pos.y = get_player_xy_position(var->map.map).y;
	var->dir = get_first_player_direction(var,
			var->map.map[(int)var->pos.x][(int)var->pos.y]);
	var->map.map[(int)var->pos.x][(int)var->pos.y] = 'P';
	var->image = mlx_new_image(var->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	mlx_image_to_window(var->mlx, var->image, 0, 0);
	var->texture.buffer = ft_calloc((SCREEN_HEIGHT) * sizeof(uint32_t *));
	while (++i < SCREEN_HEIGHT)
		var->texture.buffer[i] = ft_calloc(sizeof(uint32_t) * (SCREEN_WIDTH));
}
