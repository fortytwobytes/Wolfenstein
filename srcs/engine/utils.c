/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouakch <onouakch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 20:33:46 by onouakch          #+#    #+#             */
/*   Updated: 2023/05/18 20:33:49 by onouakch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/srcs.h"

static void	init_values(t_vect_i *inc, t_vect_i p0, t_vect_i p1,
				t_vect_i *delta);

uint32_t	get_image_color(mlx_image_t *image, t_vect_i p)
{
	uint32_t	color;
	uint32_t	index;

	index = (p.y % image->height * image->width + p.x % image->width) * 4;
	color = image->pixels[index] << 24;
	color |= image->pixels[index + 1] << 16;
	color |= image->pixels[index + 2] << 8;
	color |= 0x000000FF;
	return (color);
}

void	draw_line(mlx_image_t *image, t_vect_i p0, t_vect_i p1, uint32_t color)
{
	int			err;
	int			e2;
	t_vect_i	increment_step;
	t_vect_i	delta;

	init_values(&increment_step, p0, p1, &delta);
	err = delta.x + delta.y;
	while (true)
	{
		mlx_put_pixel(image, p0.x, p0.y, color);
		if (p0.x == p1.x && p0.y == p1.y)
			break ;
		e2 = 2 * err;
		if (e2 >= delta.y)
		{
			err += delta.y;
			p0.x += increment_step.x;
		}
		if (e2 <= delta.x)
		{
			err += delta.x;
			p0.y += increment_step.y;
		}
	}
}

static void	init_values(t_vect_i *inc, t_vect_i p0, t_vect_i p1,
		t_vect_i *delta)
{
	delta->x = +abs(p1.x - p0.x);
	delta->y = -abs(p1.y - p0.y);
	inc->x = 1;
	inc->y = 1;
	if (p1.x < p0.x)
		inc->x = -1;
	if (p1.y < p0.y)
		inc->y = -1;
}
