/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouakch <onouakch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 20:39:36 by onouakch          #+#    #+#             */
/*   Updated: 2023/04/19 21:10:36 by onouakch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/srcs.h"

void	skip_till_first_map_line(int fd, t_map *map)
{
	char	*line;

	while (true)
	{
		line = readline_skipping_spaces(fd);
		if (line == NULL)
			break ;
		if (strcmp(line, map->first_map_line) == 0)
		{
			free(line);
			break ;
		}
		free(line);
	}
}

// TODO: hold the mlx image instead of freeing it
char	*get_texture(t_var *var, char *path)
{
	// int		img_height;
	// int		img_width;
	// void	*img;
	// img = mlx_xpm_file_to_image(var->mlx.mlx, path, &img_width, &img_height);
	// if (img == NULL)
	// 	fatal("invalid texture");
	// mlx_destroy_image(var->mlx.mlx, img);
	// return (path);
	return (path);
}

void	get_map_dimentions(int fd, t_map *map)
{
	char	*line;
	int		line_len;
	char	*rest_map;

	map->max_width = ft_strlen(map->first_map_line) - 1;
	while (true)
	{
		line = get_next_line(fd);
		if (line == NULL || strcmp(line, "\n") == 0)
			break ;
		line_len = ft_strlen(line) - 1;
		if (line_len > map->max_width)
			map->max_width = line_len;
		map->max_height++;
		map->last_map_line = line;
		free(line);
	}
	rest_map = readline_skipping_spaces(fd);
	if (rest_map != NULL)
	{
		free(rest_map);
		fatal("elements after map");
	}
}
