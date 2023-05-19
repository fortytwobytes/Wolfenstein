/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouakch <onouakch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 01:02:01 by relkabou          #+#    #+#             */
/*   Updated: 2023/05/19 17:31:33 by onouakch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/srcs.h"

static bool	is_all_spaces(const char *line);

char	*readline_skipping_spaces(int fd)
{
	char	*line;

	while (true)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (is_all_spaces(line) == true || ft_strcmp(line, "\n") == 0)
		{
			free(line);
			continue ;
		}
		return (line);
	}
	return (NULL);
}

static bool	is_all_spaces(const char *line)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (line[i] != ' ' && line[i] != '\t')
			return (false);
	}
	return (true);
}

int	check(t_map *map, int l_index, int i)
{
	if (is_player(map->map[l_index][i]))
	{
		if (ft_strchr(" \t", map->map[l_index][i + 1]) || (i
				&& ft_strchr(" \t", map->map[l_index][i - 1])))
			return (-1);
		if (l_index != 0 && ft_strchr(" \t", map->map[l_index - 1][i]))
			return (-1);
		if (l_index != map->height - 1 && ft_strchr(" \t", map->map[l_index
					+ 1][i]))
			return (-1);
	}
	else if (ft_strchr(" \t", map->map[l_index][i]))
	{
		if (map->map[l_index][i + 1] == '0' || (i && map->map[l_index][i
					- 1] == '0'))
			return (-1);
		if (l_index != 0 && map->map[l_index - 1][i] == '0')
			return (-1);
		if (l_index != map->height - 1 && map->map[l_index + 1][i] == '0')
			return (-1);
	}
	return (0);
}
