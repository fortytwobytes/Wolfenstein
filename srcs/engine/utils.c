/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relkabou <relkabou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 00:52:13 by relkabou          #+#    #+#             */
/*   Updated: 2023/05/08 00:52:13 by relkabou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/srcs.h"

static void init_values(t_vect_i *inc, t_vect_i p0, t_vect_i p1, t_vect_i *delta);

void	draw_line(mlx_image_t *image, t_vect_i p0, t_vect_i p1, uint32_t color)
{
	int	err;
    int e2;
	t_vect_i s;
	t_vect_i delta;

    init_values(&s, p0, p1, &delta);
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
			p0.x += s.x;
		}
		if (e2 <= delta.x)
		{
			err += delta.x;
			p0.y += s.y;
		}
	}
}

static void init_values(t_vect_i *inc, t_vect_i p0, t_vect_i p1, t_vect_i *delta)
{
    delta->x = + abs(p1.x - p0.x);
    delta->y = - abs(p1.y - p0.y);
    inc->x = 1;
    if (p1.x < p0.x)
        inc->x = -1;
    inc->y = 1;
    if (p1.y < p0.y)
        inc->y = -1;
}
