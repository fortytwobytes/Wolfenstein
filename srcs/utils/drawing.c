/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relkabou <relkabou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 17:52:44 by relkabou          #+#    #+#             */
/*   Updated: 2023/05/06 17:53:00 by relkabou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/srcs.h"

void	draw_vert_line(mlx_image_t *image, int x, int drawStart, int drawEnd)
{
	while (drawStart < drawEnd)
		mlx_put_pixel(image, x, drawStart++, 0xff0000ff);
}

void draw_floor_ceil(t_var *var)
{
	int i;
	int j;

	i = -1;
	while (++i < SCREEN_HEIGHT / 2) {
		j = -1;
		while (++j < SCREEN_WIDTH)
			mlx_put_pixel(var->image, j, i, var->map.f_color);
	}
	while (++i < SCREEN_HEIGHT) {
		j = -1;
		while (++j < SCREEN_WIDTH)
			mlx_put_pixel(var->image, j, i, var->map.c_color);
	}
}

void	draw_direction(void *args, char **minimap, int32_t color)
{
	t_var *var = (t_var *)args;
	t_vect_i player_pos = get_player_xy_position(minimap);
	t_vect_f pos;
	pos.x = player_pos.x * MINI_CUB_SIZE + 8 / 2;
	pos.y = player_pos.y * MINI_CUB_SIZE + 8 / 2;
	draw_line(var->image, pos, (t_vect_f) {pos.x + var->dir.x * 30, pos.y + var->dir.y * 30}, color);

}

void	mlx_draw_circle(mlx_image_t *image, int x, int y, int size, uint32_t color) {

	int radius = size / 2;
	int cx = x + radius;
	int cy = y + radius;

	for (int i = x; i < x + size; i++) {
		for (int j = y; j < y + size; j++) {
			int dx = i - cx;
			int dy = j - cy;
			if (dx * dx + dy * dy <= radius * radius) {
				mlx_put_pixel(image, i, j, color);
			}
		}
	}
}

void mlx_draw_square(mlx_image_t *image, int x, int y, int size, uint32_t color) {
	int x_end = x + size;
	int y_end = y + size;

	int j = y;

	while (x < x_end) {
		y = j;
		while (y < y_end) {
			mlx_put_pixel(image, x, y, color);
			y++;
		}
		x++;
	}
}
