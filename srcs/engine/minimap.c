/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relkabou <relkabou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 01:02:20 by relkabou          #+#    #+#             */
/*   Updated: 2023/05/07 01:02:20 by relkabou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/srcs.h"

char	**get_small_map(t_var *var)
{
	t_vect_i	player_pos;
	char		**map;

	player_pos = get_player_xy_position(var->map.map);
	var->map.map[player_pos.x][player_pos.y] = '0';
	var->map.map[(int)var->pos.x][(int)var->pos.y] = 'P';
	map = get_minimap(var->map.map);
	return (map);
}

// 11 is the height and width in the minimap (char**)
char	**get_minimap(char **realMap)
{
	t_minimap	m;

	m.i = -1;
	m.player_pos = get_player_xy_position(realMap);
	m.minimap = ft_calloc(sizeof(char *) * (11 + 1));
	m.p.x = m.player_pos.x - 5;
	m.map.x = (int)ft_strlen(realMap[0]);
	m.map.y = 0;
	while (realMap[m.map.y])
		m.map.y++;
	while (++m.i < 11)
	{
		m.j = -1;
		m.p.y = m.player_pos.y - 5;
		m.minimap[m.i] = ft_calloc(sizeof(char) * (11 + 1));
		ft_memset(m.minimap[m.i], '1', 11);
		while (++m.j < 11)
		{
			if (m.p.x >= 0 && m.p.y >= 0 && m.p.x < m.map.y && m.p.y < m.map.x)
				m.minimap[m.i][m.j] = realMap[m.p.x][m.p.y];
			m.p.y++;
		}
		m.p.x++;
	}
	return (m.minimap);
}

void	draw_mini_map(t_var *data, char **miniMap)
{
	t_vect_i	p;
	t_idxs		idx;

	p.x = -1;
	idx.i = 0;
	draw_square(data->image, (t_vect_i){0, 0}, 11 * MINI_CUB_SIZE, WHITE);
	while (miniMap[++p.x])
	{
		idx.j = 0;
		p.y = -1;
		while (miniMap[p.x][++p.y])
		{
			if (miniMap[p.x][p.y] == '1')
				draw_square(data->image, (t_vect_i){idx.i, idx.j},
						MINI_CUB_SIZE, BLACK);
			else if (miniMap[p.x][p.y] == '0')
				draw_square(data->image, (t_vect_i){idx.i, idx.j},
						MINI_CUB_SIZE, WHITE);
			else if (miniMap[p.x][p.y] == 'P')
				draw_circle(data->image, (t_vect_i){idx.i, idx.j}, PLAYER_SIZE,
						RED);
			idx.j += MINI_CUB_SIZE;
		}
		idx.i += MINI_CUB_SIZE;
	}
	draw_direction(data, miniMap, RED);
	free_split(miniMap);
}
