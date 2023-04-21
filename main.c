/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relkabou <relkabou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 14:13:34 by relkabou          #+#    #+#             */
/*   Updated: 2023/04/18 14:58:47 by relkabou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/srcs.h"

int main(int ac, char **av) {
    t_var var;

    if (ac != 2) {
        fatal("invalid arguments");
    }
    init_window(&var);
    parsing(&var, av[1]);

    init_images(&var);

    draw_map(&var);
    draw_player(var.player.img);

    mlx_loop_hook(var.mlx, hooks, &var);
    mlx_loop(var.mlx);
    mlx_terminate(var.mlx);
    return (0);
}

