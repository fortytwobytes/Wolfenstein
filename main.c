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

static void init_mlx(t_var *var);
void draw_player(void *params);
void draw_map(void *params);
void draw_square(t_var *var, int x, int y, u_int32_t color);

int main(int ac, char **av) {
    t_var var;

    if (ac != 2) {
        fatal("invalid arguments");
    }
    init_mlx(&var);
    parsing(&var, av[1]);

    draw_map(&var);
    draw_player(var.img);

    mlx_loop_hook(var.mlx, hooks, &var);
    mlx_loop(var.mlx);
    mlx_terminate(var.mlx);
    for (int i = 0; var.map.map[i]; ++i)
        puts(var.map.map[i]);
    return (0);
}

// TODO:
//  check the whether using the resize option or not
//  find a good relationship between the window size, map line and cube size
static void init_mlx(t_var *var) {
    var->mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "Wolf3D", false);
    if (var->mlx == NULL) {
        fatal(mlx_strerror(mlx_errno));
    }
    // mlx_set_window_limit(var->mlx, WIN_WIDTH, WIN_HEIGHT, WIN_WIDTH, WIN_HEIGHT);
    var->map_img = mlx_new_image(var->mlx, WIN_WIDTH, WIN_HEIGHT);
    if (var->map_img == NULL) {
        mlx_close_window(var->mlx);
        fatal(mlx_strerror(mlx_errno));
    }
    var->img = mlx_new_image(var->mlx, PLAYER_SIZE, PLAYER_SIZE);
    if (var->img == NULL) {
        mlx_close_window(var->mlx);
        fatal(mlx_strerror(mlx_errno));
    }
    if (mlx_image_to_window(var->mlx, var->map_img, 0, 0) == EOF) {
        mlx_close_window(var->mlx);
        fatal(mlx_strerror(mlx_errno));
    }
    // TODO: maybe we need to pass the player position instead of (0, 0)
    if (mlx_image_to_window(var->mlx, var->img, 0, 0) == EOF) {
        mlx_close_window(var->mlx);
        fatal(mlx_strerror(mlx_errno));
    }
}

void draw_player(void *params) {
    mlx_image_t *img = params;
    for (int x = 0; x < img->width; ++x) {
        for (int y = 0; y < img->height; ++y) {
            mlx_put_pixel(img, x, y, 0XFF0000FF);
        }
    }
}

void draw_map(void *params) {
    t_var *var = params;

    int i = 0;
    for (int x = 0; var->map.map[i]; x += var->map.cub_size) {
        int j = 0;
        char *line = var->map.map[i];
        for (int y = 0; line[j]; y += var->map.cub_size) {
            if (line[j] == '1')
                draw_square(var, x, y, 0xFFFFFFFF);
            if (line[j] == '0')
                draw_square(var, x, y, 0x000000FF);
            j++;
        }
        i++;
    }
}

void draw_square(t_var *var, int x, int y, u_int32_t color) {
    int xEnd = x + var->map.cub_size - 1;
    int yEnd = y + var->map.cub_size - 1;
    for (int xo = x; xo < xEnd; xo++) {
        for (int yo = y; yo < yEnd; yo++) {
            mlx_put_pixel(var->map_img, xo, yo, color);
        }
    }
}
