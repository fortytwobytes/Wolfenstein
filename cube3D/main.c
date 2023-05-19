/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouakch <onouakch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 17:09:19 by onouakch          #+#    #+#             */
/*   Updated: 2023/05/19 17:21:52 by onouakch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/srcs.h"

int32_t	main(int32_t argc, const char *argv[])
{
	t_var	var;

	if (argc != 2)
		fatal("Usage: ./cub3D <map.cub>\n");
	init_window(&var);
	parsing(&var, argv[1]);
	init(&var);
	mlx_loop_hook(var.mlx, move_hook, &var);
	mlx_loop_hook(var.mlx, draw_hook, &var);
	mlx_key_hook(var.mlx, switch_mouse_mode, &var);
	mlx_close_hook(var.mlx, end_game, &var);
	mlx_loop(var.mlx);
	mlx_terminate(var.mlx);
	return (EXIT_SUCCESS);
}

void	end_game(void *param)
{
	int		i;
	t_var	*var;

	i = -1;
	var = (t_var *)param;
	free_split(var->map.map);
	mlx_delete_image(var->mlx, var->image);
	mlx_close_window(var->mlx);
	while (++i < SCREEN_HEIGHT)
		free(var->texture.buffer[i]);
	free(var->texture.buffer);
	exit(0);
}
