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

void	draw_line(mlx_image_t *image, t_vect_f p1, t_vect_f p2, uint color)
{
	int	x0;
	int	y0;
	int	x1;
	int	y1;
	int	dx;
	int	dy;
	int	err;
    int sx;
    int sy;
    int e2;

	x0 = (int)p1.x;
	y0 = (int)p1.y;
	x1 = (int)p2.x;
	y1 = (int)p2.y;
	dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
	dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
	err = dx + dy, e2;
	while (true)
	{
		mlx_put_pixel(image, x0, y0, color);
		if (x0 == x1 && y0 == y1)
			break ;
		e2 = 2 * err;
		if (e2 >= dy)
		{
			err += dy;
			x0 += sx;
		}
		if (e2 <= dx)
		{
			err += dx;
			y0 += sy;
		}
	}
}
