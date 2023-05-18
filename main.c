/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouakch <onouakch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 17:09:19 by onouakch          #+#    #+#             */
/*   Updated: 2023/05/18 17:12:03 by onouakch         ###   ########.fr       */
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
	mlx_loop(var.mlx);
	mlx_terminate(var.mlx);
	return (EXIT_SUCCESS);
}

void	end_game(t_var *var)
{
	int	i;

	i = -1;
	free_split(var->map.map);
	mlx_delete_image(var->mlx, var->image);
	mlx_close_window(var->mlx);
	while (++i < SCREEN_HEIGHT)
		free(var->texture.buffer[i]);
	free(var->texture.buffer);
	exit(0);
}
