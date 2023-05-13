/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relkabou <relkabou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 17:09:19 by onouakch          #+#    #+#             */
/*   Updated: 2023/05/08 01:45:21 by relkabou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/srcs.h"

// TODO: add mlx_terminate later
int32_t main(int32_t argc, const char *argv[]) {
	t_var var;

	if (argc != 2)
		fatal("Usage: ./cub3D <map.cub>\n");
	init_window(&var);
	parsing(&var, argv[1]);
	init(&var);
	mlx_loop_hook(var.mlx, move_hook, &var);
	mlx_loop_hook(var.mlx, draw_hook, &var);
	mlx_loop(var.mlx);
	return (EXIT_SUCCESS);
}

void	end_game(t_var *var)
{
	free_split(var->map.map);
	mlx_delete_image(var->mlx, var->image);
	mlx_close_window(var->mlx);
	exit(0);
}
