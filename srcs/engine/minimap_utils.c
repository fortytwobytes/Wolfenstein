/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouakch <onouakch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 20:16:29 by onouakch          #+#    #+#             */
/*   Updated: 2023/05/18 20:21:42 by onouakch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/srcs.h"

t_vect_i	fix_coor(int x, int y, int size)
{
	t_vect_i	result;

	result.x = x;
	result.y = size - y;
	return (result);
}

void	check_cube(t_var *data, char **miniMap, t_idxs idx, t_vect_i p)
{
	if (miniMap[p.x][p.y] == '1')
		draw_square(data->image, fix_coor(idx.i, idx.j, 10 * MINI_CUB_SIZE),
			MINI_CUB_SIZE, BLACK);
	else if (miniMap[p.x][p.y] == '0')
		draw_square(data->image, fix_coor(idx.i, idx.j, 10 * MINI_CUB_SIZE),
			MINI_CUB_SIZE, WHITE);
	else if (miniMap[p.x][p.y] == 'P')
		draw_circle(data->image, fix_coor(idx.i, idx.j, 10 * MINI_CUB_SIZE),
			PLAYER_SIZE, RED);
}
