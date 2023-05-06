/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relkabou <relkabou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 17:09:19 by onouakch          #+#    #+#             */
/*   Updated: 2023/05/04 17:19:28 by relkabou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/srcs.h"
#include <time.h>
#include "lib/MLX42/include/MLX42/MLX42.h"

void	end_game(t_var *var) {
	free_split(var->map.map);
	mlx_delete_image(var->mlx, var->image);
	mlx_close_window(var->mlx);
	exit(0);
}

void init(t_var *var) {
	var->pos.x = get_player_xy_position(var->map.map).x;
	var->pos.y = get_player_xy_position(var->map.map).y;
	// we should change this to get the first player direction
//	var->dir.x = get_first_player_direction(worldMap[(int)data->pos.x][(int)data->pos.y]).x;
//	var->dir.y = get_first_player_direction(worldMap[(int)data->pos.x][(int)data->pos.y]).y;
	var->dir.x = -1.0;
	var->dir.y = 0.0;
	var->plane.x = 0;
	var->plane.y = 0.66;
	var->c_time = 0;
	var->old_time = 0;
	var->image = mlx_new_image(var->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	mlx_image_to_window(var->mlx, var->image, 0, 0);
}

int32_t main(int32_t argc, const char *argv[]) {
	t_var var;

	if (argc != 2) {
		fatal("Usage: ./cub3D <map.cub>\n");
	}
	init_window(&var);
	parsing(&var, argv[1]);
	init(&var);

	mlx_loop_hook(var.mlx, move_hook, &var);
	mlx_loop_hook(var.mlx, draw_hook, &var);

	mlx_loop(var.mlx);
//	mlx_terminate(var.mlx);
	return (EXIT_SUCCESS);
}
