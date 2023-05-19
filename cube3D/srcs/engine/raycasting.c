/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relkabou <relkabou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 14:25:34 by relkabou          #+#    #+#             */
/*   Updated: 2023/05/07 14:25:34 by relkabou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/srcs.h"

void	resetting_ray(t_var *var, t_ray *ray, int xPixel)
{
	ray->camera_x = 2 * xPixel / (double)SCREEN_WIDTH - 1;
	ray->ray_dir_x = var->dir.x + var->plane.x * ray->camera_x;
	ray->ray_dir_y = var->dir.y + var->plane.y * ray->camera_x;
	ray->map_x = (int)var->pos.x;
	ray->map_y = (int)var->pos.y;
	if (ray->ray_dir_x == 0)
		ray->delta_dist_x = 1.0;
	else
		ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	if (ray->ray_dir_y == 0)
		ray->delta_dist_y = 1.0;
	else
		ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
}

void	set_step_and_side_distances(t_var *var, t_ray *ray)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (var->pos.x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - var->pos.x) * ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (var->pos.y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - var->pos.y) * ray->delta_dist_y;
	}
}

void	cast_ray_till_wall(t_var *var, t_ray *ray, int *side)
{
	while (true)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			*side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			*side = 1;
		}
		if (var->map.map[ray->map_x][ray->map_y] == '1')
			break ;
	}
}

void	calculate_line_properties(t_ray *ray, int side)
{
	ray->perp_wall_dist = (ray->side_dist_y - ray->delta_dist_y);
	if (side == 0)
		ray->perp_wall_dist = (ray->side_dist_x - ray->delta_dist_x);
	ray->line.line_height = (int)(SCREEN_HEIGHT / ray->perp_wall_dist);
	ray->line.draw_start = -ray->line.line_height / 2 + SCREEN_HEIGHT / 2;
	if (ray->line.draw_start < 0)
		ray->line.draw_start = 0;
	ray->line.draw_end = ray->line.line_height / 2 + SCREEN_HEIGHT / 2;
	if (ray->line.draw_end >= SCREEN_HEIGHT)
		ray->line.draw_end = SCREEN_HEIGHT - 1;
}
