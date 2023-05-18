/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouakch <onouakch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 17:52:44 by relkabou          #+#    #+#             */
/*   Updated: 2023/05/18 14:34:20y onouakch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/srcs.h"

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
