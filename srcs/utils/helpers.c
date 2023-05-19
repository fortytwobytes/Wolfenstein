/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouakch <onouakch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 00:51:11 by relkabou          #+#    #+#             */
/*   Updated: 2023/05/18 20:34:56 by onouakch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/srcs.h"

void	free_split(char **split)
{
	int	i;

	i = -1;
	while (split[++i])
		free(split[i]);
	free(split);
}

t_vect_i	get_player_xy_position(char **realMap)
{
	int	x;
	int	y;

	x = -1;
	while (realMap[++x])
	{
		y = -1;
		while (realMap[x][++y])
		{
			if (ft_strchr("NEWSP", realMap[x][y]))
				return ((t_vect_i){x, y});
		}
	}
	fatal("No player found");
	return ((t_vect_i){-1, -1});
}

t_vect_f	get_first_player_direction(t_var *var, char direction)
{
	t_vect_f	dir;

	dir = (t_vect_f){0.0, -1.0};
	var->plane.x = -0.66;
	var->plane.y = 0;
	if (direction == 'N')
	{
		dir = (t_vect_f){-1.0, 0.0};
		var->plane.x = 0;
		var->plane.y = 0.66;
	}
	else if (direction == 'S')
	{
		dir = (t_vect_f){1.0, 0.0};
		var->plane.x = 0;
		var->plane.y = -0.66;
	}
	else if (direction == 'E')
	{
		dir = (t_vect_f){0.0, 1.0};
		var->plane.x = 0.66;
		var->plane.y = 0;
	}
	return (dir);
}
