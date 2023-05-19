/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouakch <onouakch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 20:26:28 by onouakch          #+#    #+#             */
/*   Updated: 2023/05/18 20:33:01 by onouakch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/srcs.h"

void	set_texture_params(t_var *var)
{
	double	wall_x;

	if (var->texture.side == 0)
		wall_x = var->pos.y + var->ray.perp_wall_dist * var->ray.ray_dir_y;
	else
		wall_x = var->pos.x + var->ray.perp_wall_dist * var->ray.ray_dir_x;
	wall_x -= floor((wall_x));
	var->texture.tex_x = (int)(wall_x * (double)(CUBE_SIZE));
	if (var->texture.side == 0 && var->ray.ray_dir_x > 0)
		var->texture.tex_x = CUBE_SIZE - var->texture.tex_x - 1;
	if (var->texture.side == 1 && var->ray.ray_dir_y < 0)
		var->texture.tex_x = CUBE_SIZE - var->texture.tex_x - 1;
	var->texture.step = 1.0 * CUBE_SIZE / var->ray.line.line_height;
	var->texture.pos = (var->ray.line.draw_start - SCREEN_HEIGHT / 2
			+ var->ray.line.line_height / 2) * var->texture.step;
}

void	set_env(t_var *var)
{
	int	i;
	int	j;

	i = -1;
	while (++i < SCREEN_WIDTH)
	{
		j = -1;
		while (++j < SCREEN_HEIGHT && !var->texture.buffer[j][i])
			var->texture.buffer[j][i] = var->map.f_color;
	}
	i = -1;
	while (++i < SCREEN_WIDTH)
	{
		j = SCREEN_HEIGHT;
		while (--j >= 0 && !var->texture.buffer[j][i])
			var->texture.buffer[j][i] = var->map.c_color;
	}
}

void	draw_3d_scene(t_var *var)
{
	int	i;
	int	j;

	i = -1;
	set_env(var);
	while (++i < SCREEN_WIDTH)
	{
		j = -1;
		while (++j < SCREEN_HEIGHT)
			mlx_put_pixel(var->image, i, j, var->texture.buffer[j][i]);
	}
	i = -1;
	while (++i < SCREEN_HEIGHT)
	{
		j = -1;
		while (++j < SCREEN_WIDTH)
			var->texture.buffer[i][j] = 0;
	}
}

void	fill_texture_buffer(t_var *var, int x, int drawStart, int drawEnd)
{
	int			tex_y;
	int			y;
	t_vect_i	cord;

	y = drawStart - 1;
	while (++y < drawEnd)
	{
		tex_y = (int)var->texture.pos & (CUBE_SIZE - 1);
		var->texture.pos += var->texture.step;
		cord = (t_vect_i){var->texture.tex_x, tex_y};
		if (var->texture.side == 0 && var->ray.ray_dir_x > 0)
			var->texture.buffer[y][x] = get_image_color(var->map.so_image,
					cord);
		else if (var->texture.side == 0)
			var->texture.buffer[y][x] = get_image_color(var->map.no_image,
					cord);
		else if (var->ray.ray_dir_y > 0)
			var->texture.buffer[y][x] = get_image_color(var->map.ea_image,
					cord);
		else
			var->texture.buffer[y][x] = get_image_color(var->map.we_image,
					cord);
	}
}
