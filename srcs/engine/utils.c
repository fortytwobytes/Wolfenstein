/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relkabou <relkabou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 16:45:29 by relkabou          #+#    #+#             */
/*   Updated: 2023/04/25 16:45:29 by relkabou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/srcs.h"

double	distance_between_points(double x1, double y1, double x2, double y2)
{
	return (sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)));
}

void	draw_line(mlx_image_t *image, t_vect_i p0, t_vect_i p1, uint32_t color)
{
	int	err;
    int e2;
	t_vect_i s;
	t_vect_i delta;

	delta.x = abs(p1.x - p0.x), s.x = p0.x < p1.x ? 1 : -1;
	delta.y = -abs(p1.y - p0.y), s.y = p0.y < p1.y ? 1 : -1;
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
