/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouakch <onouakch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 13:24:35 by onouakch          #+#    #+#             */
/*   Updated: 2023/04/16 16:13:23 by onouakch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "srcs.h"

int ft_is_wall(char *wall)
{
    int i;

    i = -1;
    while (wall[++i])
        if (wall[i] != ' ' && wall[i] != '1')
            return (free(wall), -1);
    return (free(wall), 0);
}

int ft_check_ledges(char *map_line)
{
    if (map_line[0] != '1' || map_line[ft_strlen(map_line) - 1] != '1')
        return (free(map_line), -1);
    return (0);
}

int ft_check_content(char *line, t_var *var, int y)
{
    int i;

    i = -1;
    while (line[++i])
    {
        if (line[i] != '0' && line[i] != '1' && line[i] != 'N' && line[i] != 'S'
            && line[i] != 'E' && line[i] != 'W' && line[i] != ' ' 
            && line[i] != '\t')
            return (free(line), -1);
        else if (line[i] == 'N' || line[i] == 'S'
            || line[i] == 'E' || line[i] == 'W')
        {
            if (var->player.first_view != '\0')
                return (free(line), -1);
            var->player.position.x = i;
            var->player.position.y = y;
            var->player.first_view = line[i];
        }
    }
    return (0);
}

int ft_check_spaces(t_map *map, int l_index)
{
    int i;

    i = -1;
    while (map->map[l_index][++i])
    {
        if (map->map[l_index][i] == ' ' || map->map[l_index][i] == '\t')
        {
            if (map->map[l_index][i + 1] == '0'
                || map->map[l_index][i - 1] == '0')
                    return (-1);
            if (l_index != 0 && map->map[l_index - 1][i] == '0')
                return (-1);
            if (l_index != map->max_height - 1
                &&  map->map[l_index + 1][i] == '0')
                return (-1);
        }
    }
    return (0);
}

// void    check_orders(char *element, int order)
// {
//     char    *orders[7];

//     orders[0] = "NO";
//     orders[1] = "SO";
//     orders[2] = "WE";
//     orders[3] = "EA";
//     orders[4] = "F";
//     orders[5] = "C";
//     orders[6] = NULL;

//     if (strcmp(orders[order], element) != 0)
//         fatal("orders error");
// }

int ft_check_map(t_var *var)
{
    int i;
    char    *map_line;
    if (ft_is_wall(ft_strtrim(var->map.map[0], SPACES)) ||
        ft_is_wall(ft_strtrim(var->map.map[var->map.max_height - 1], SPACES)))
        fatal("walls error");
    i = -1;
    while (++i < var->map.max_height - 1)
    {
        map_line = ft_strtrim(var->map.map[i], " ");
        if (ft_check_ledges(map_line))
            fatal("ledges error");
        if (ft_check_content(map_line, var, i))
            fatal("content error");
        if (ft_strchr(map_line, ' ') || ft_strchr(map_line, '\t'))
            if (ft_check_spaces(&var->map, i))
                fatal("exit error");
    }
    if (var->player.first_view == '\0')
        fatal("player error");
    return (0);
}