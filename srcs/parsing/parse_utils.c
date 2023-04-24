/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouakch <onouakch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 20:39:36 by onouakch          #+#    #+#             */
/*   Updated: 2023/04/24 07:35:02 by relkabou         ###   ########.fr       */
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

mlx_image_t *get_texture(t_var *var, char *path)
{
	xpm_t *xpm = mlx_load_xpm42(path);
	if (xpm == NULL)
		fatal("invalid xpm texture");
    mlx_image_t *image = mlx_texture_to_image(var->mlx, &xpm->texture);
    if (image == NULL) {
        mlx_delete_xpm42(xpm);
        fatal(mlx_strerror(mlx_errno));
    }
	return (image);
}

void	get_map_dimension(int fd, t_map *map)
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
		free(line);
	}
	rest_map = readline_skipping_spaces(fd);
	if (rest_map != NULL)
	{
		free(rest_map);
		fatal("elements after map");
	}
}

u_int32_t get_color(int *rgb)
{
	ushort red;
	ushort green;
	ushort blue;

	red = rgb[0];
	green = rgb[1];
	blue = rgb[2];
	return (red << 24 | green << 16 | blue << 8 | 0xFF);
}