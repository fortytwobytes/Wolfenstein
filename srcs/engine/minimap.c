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
	t_vect_i player_pos;
	char	**map;

	player_pos = get_player_xy_position(var->map.map);
	var->map.map[player_pos.x][player_pos.y] = '0';
	var->map.map[(int) var->pos.x][(int) var->pos.y] = 'P';
	map = get_minimap(var->map.map);
	return (map);
}

char	**get_minimap(char **realMap)
{
	char		**minimap;
	int			i;
	t_vect_i	player_pos;
	int			x;
	size_t		map_width;
	size_t		map_height;
	int			j;
	int			y;

	i = -1;
	player_pos = get_player_xy_position(realMap);
	minimap = ft_calloc(sizeof(char *) * (11 + 1));
	x = player_pos.x - 5;
	map_width = ft_strlen(realMap[0]);
	map_height = 0;
	while (realMap[map_height])
		map_height++;
	while (++i < 11)
	{
		j = -1;
		y = player_pos.y - 5;
		minimap[i] = ft_calloc(sizeof(char) * (11 + 1));
		ft_memset(minimap[i], '1', 11);
		while (++j < 11)
		{
			if (x >= 0 && y >= 0 && x < map_height && y < map_width)
				minimap[i][j] = realMap[x][y];
			y++;
		}
		x++;
	}
	minimap[i] = NULL;
	return (minimap);
}

void	draw_mini_map(t_var *data, char **miniMap)
{
	int	i;
	int	j;
	int	x;
	int	y;

	x = 0;
	i = 0;
	mlx_draw_square(data->image, 0, 0, 11 * MINI_CUB_SIZE, WHITE);
	while (miniMap[x])
	{
		j = 0;
		y = 0;
		while (miniMap[x][y])
		{
			if (miniMap[x][y] == '1')
				mlx_draw_square(data->image, i, j, MINI_CUB_SIZE, BLACK);
			else if (miniMap[x][y] == '0')
				mlx_draw_square(data->image, i, j, MINI_CUB_SIZE, WHITE);
			// to change this condition later
			else if (miniMap[x][y] == 'N' || miniMap[x][y] == 'S'
					|| miniMap[x][y] == 'E' || miniMap[x][y] == 'W'
					|| miniMap[x][y] == 'P')
				mlx_draw_circle(data->image, i, j, PLAYER_SIZE, RED);
			j += MINI_CUB_SIZE;
			y++;
		}
		i += MINI_CUB_SIZE;
		x++;
	}
	draw_direction(data, miniMap, RED);
	free_split(miniMap);
}
