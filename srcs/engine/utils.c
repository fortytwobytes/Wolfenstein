/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relkabou <relkabou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 16:45:29 by relkabou          #+#    #+#             */
/*   Updated: 2023/04/25 16:45:29 by relkabou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/srcs.h"

static int32_t get_incrementation(int p1, int p2)
{
    if (p1 < p2)
        return (1);
    return (-1);
}

double distance_between_points(double x1, double y1, double x2, double y2)
{
    return (sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)));
}

// err * 2 is used to calculate this error for the next iteration.
void    draw_line(mlx_image_t *image, t_vect p1, t_vect p2, uint color)
{
    t_vect  incr;
    t_vect  delta;
    int     err;

    delta.x = +(int)fabs(p1.x - p2.x);
    delta.y = -(int)fabs(p1.y - p2.y);
    incr.x = get_incrementation((int)p1.x, (int)p2.x);
    incr.y = get_incrementation((int)p1.y, (int)p2.y);
    err = (int)(delta.x + delta.y);
    while (true)
    {
        mlx_put_pixel(image, (uint)p1.x, (uint)p1.y, color);
        if ((int)p1.x == (int)p2.x && (int)p1.y == (int)p2.y)
            break ;
        if (err * 2 >= (int)delta.y)
        {
            err += (int)delta.y;
            p1.x += incr.x;
        }
        if (err * 2 <= (int)delta.x)
        {
            err += (int)delta.x;
            p1.y += incr.y;
        }
    }
}
