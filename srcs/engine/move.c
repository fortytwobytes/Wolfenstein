/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relkabou <relkabou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 00:43:56 by relkabou          #+#    #+#             */
/*   Updated: 2023/05/07 00:46:32 by relkabou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/srcs.h"

static bool	can_move(char block);

void	move_forward(t_var *var, double moveSpeed)
{
	if (can_move(var->map.map[(int)(var->pos.x + var->dir.x
				* moveSpeed)][(int)(var->pos.y)]))
		var->pos.x += var->dir.x * moveSpeed;
	if (can_move(var->map.map[(int)(var->pos.x)][(int)(var->pos.y + var->dir.y
				* moveSpeed)]))
		var->pos.y += var->dir.y * moveSpeed;
}

void	move_backward(t_var *var, double moveSpeed)
{
	if (can_move(var->map.map[(int)(var->pos.x - var->dir.x
				* moveSpeed)][(int)(var->pos.y)]))
		var->pos.x -= var->dir.x * moveSpeed;
	if (can_move(var->map.map[(int)(var->pos.x)][(int)(var->pos.y - var->dir.y
				* moveSpeed)]))
		var->pos.y -= var->dir.y * moveSpeed;
}

void	move_left(t_var *var, double moveSpeed)
{
	double	new_x;
	double	new_y;

	new_x = var->pos.x - var->plane.x * moveSpeed;
	new_y = var->pos.y - var->plane.y * moveSpeed;
	if (can_move(var->map.map[(int)new_x][(int)var->pos.y]))
		var->pos.x = new_x;
	if (can_move(var->map.map[(int)var->pos.x][(int)new_y]))
		var->pos.y = new_y;
}

void	move_right(t_var *var, double moveSpeed)
{
	double	new_x;
	double	new_y;

	new_x = var->pos.x + var->plane.x * moveSpeed;
	new_y = var->pos.y + var->plane.y * moveSpeed;
	if (can_move(var->map.map[(int)new_x][(int)var->pos.y]))
		var->pos.x = new_x;
	if (can_move(var->map.map[(int)var->pos.x][(int)new_y]))
		var->pos.y = new_y;
}

static bool	can_move(char block)
{
	const char	*allowed_blocks;

	allowed_blocks = "0NSWEP";
	for (int i = 0; allowed_blocks[i]; i++)
	{
		if (block == allowed_blocks[i])
		{
			return (true);
		}
	}
	return (false);
}
