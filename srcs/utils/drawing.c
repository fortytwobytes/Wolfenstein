/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relkabou <relkabou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 17:52:44 by relkabou          #+#    #+#             */
/*   Updated: 2023/05/17 23:09:51 by relkabou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/srcs.h"

// draw.x == starting point
// draw.y == ending point
void	draw_vert_line(t_var *var, int x, t_vect_i draw, int side)
{
	while (draw.x < draw.y)
	{
		t_vect_i cord = (t_vect_i) {x, draw.x};
		if (side == 0 && var->ray.ray_dir_x > 0)
			mlx_put_pixel(var->image, x, draw.x,
				get_image_color(var->map.so_image, cord));
		else if (side == 0)
			mlx_put_pixel(var->image, x, draw.x,
				get_image_color(var->map.no_image, cord));
		else if (var->ray.ray_dir_y > 0)
			mlx_put_pixel(var->image, x, draw.x,
				get_image_color(var->map.ea_image, cord));
		else
			mlx_put_pixel(var->image, x, draw.x,
				get_image_color(var->map.we_image, cord));
		draw.x++;
	}
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

void	draw_circle(mlx_image_t *image, t_vect_i p, int size, uint32_t color)
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

void	draw_square(mlx_image_t *image, t_vect_i p, int size, uint32_t color)
{
	int	x_end;
	int	y_end;
	int	j;

	x_end = p.x + size;
	y_end = p.y + size;
	j = p.y;
	while (p.x < x_end)
	{
		p.y = j;
		while (p.y < y_end)
		{
			mlx_put_pixel(image, p.x, p.y, color);
			p.y++;
		}
		p.x++;
	}
}
