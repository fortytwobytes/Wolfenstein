/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relkabou <relkabou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 17:52:44 by relkabou          #+#    #+#             */
/*   Updated: 2023/05/08 01:14:49 by relkabou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/srcs.h"

void	draw_vert_line(mlx_image_t *image, int x, int drawStart, int drawEnd)
{
	while (drawStart < drawEnd)
		mlx_put_pixel(image, x, drawStart++, 0xff0000ff);
}

void	draw_floor_ceil(t_var *var)
{
	int	i;
	int	j;

	i = -1;
	while (++i < SCREEN_HEIGHT / 2)
	{
		j = -1;
		while (++j < SCREEN_WIDTH)
			mlx_put_pixel(var->image, j, i, var->map.f_color);
	}
	while (++i < SCREEN_HEIGHT)
	{
		j = -1;
		while (++j < SCREEN_WIDTH)
			mlx_put_pixel(var->image, j, i, var->map.c_color);
	}
}

void	draw_direction(void *args, char **minimap, uint32_t color)
{
	t_var		*var;
	t_vect_i	player_pos;
	t_vect_i	pos;
	t_vect_i	dir;

	var = (t_var *)args;
	player_pos = get_player_xy_position(minimap);
	pos.x = player_pos.x * MINI_CUB_SIZE + PLAYER_SIZE / 2;
	pos.y = player_pos.y * MINI_CUB_SIZE + PLAYER_SIZE / 2;
	dir.x = pos.x + var->dir.x * DIRECTION_LEN;
	dir.y = pos.y + var->dir.y * DIRECTION_LEN;
	draw_line(var->image, pos, dir, color);
}

void	mlx_draw_circle(mlx_image_t *image, t_vect_i p, int size, uint32_t color)
{
	int			i;
	int			j;
	int			radius;
	t_vect_i	c;
	t_vect_i	d;

	i = p.x - 1;
	radius = size / 2;
	c.x = p.x + radius;
	c.y = p.y + radius;
	while (++i < p.x + size)
	{
		j = p.y - 1;
		while (++j < p.y + size)
		{
			d.x = i - c.x;
			d.y = j - c.y;
			if (d.x * d.x + d.y * d.y <= radius * radius)
				mlx_put_pixel(image, i, j, color);
		}
	}
}

void	mlx_draw_square(mlx_image_t *image, int x, int y, int size,
		uint32_t color)
{
	int	x_end;
	int	y_end;
	int	j;

	x_end = x + size;
	y_end = y + size;
	j = y;
	while (x < x_end)
	{
		y = j;
		while (y < y_end)
		{
			mlx_put_pixel(image, x, y, color);
			y++;
		}
		x++;
	}
}
