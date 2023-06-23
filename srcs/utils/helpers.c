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

	dir = (t_vect_f) {0.0, 0.0};
    var->plane = (t_vect_f) {0.0, 0.0};
	if (direction == 'N')
	{
		var->plane.y = FOV;
        dir.x = -1.0;
	}
	else if (direction == 'E')
	{
		var->plane.x = FOV;
        dir.y = 1.0;
	}
    else if (direction == 'W')
    {
        var->plane.x = -FOV;
        dir.y = -1.0;
    }
    else if (direction == 'S')
    {
        var->plane.y = -FOV;
        dir.x = 1.0;
    }
	return (dir);
}
