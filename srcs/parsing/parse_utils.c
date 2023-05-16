/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relkabou <relkabou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 20:39:36 by onouakch          #+#    #+#             */
/*   Updated: 2023/05/08 01:06:27 by relkabou         ###   ########.fr       */
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
		if (ft_strcmp(line, map->first_map_line) == 0)
		{
			free(line);
			break ;
		}
		free(line);
	}
}

mlx_image_t	*get_texture(t_var *var, char *path)
{
	xpm_t		*xpm;
	mlx_image_t	*image;

	xpm = mlx_load_xpm42(path);
	if (xpm == NULL)
		fatal("invalid xpm texture");
	image = mlx_texture_to_image(var->mlx, &xpm->texture);
	if (image == NULL)
	{
		mlx_delete_xpm42(xpm);
		fatal(mlx_strerror(mlx_errno));
	}
	mlx_delete_xpm42(xpm);
	mlx_resize_image(image, CUBE_SIZE, CUBE_SIZE);
	return (image);
}

void	get_map_dimension(int fd, t_map *map)
{
	char	*line;
	int		line_len;
	char	*rest_map;

	map->width = ft_strlen(map->first_map_line) - 1;
	while (true)
	{
		line = get_next_line(fd);
		if (line == NULL || ft_strcmp(line, "\n") == 0)
			break ;
		line_len = ft_strlen(line) - 1;
		if (line_len > map->width)
			map->width = line_len;
		map->height++;
		free(line);
	}
	free(line);
	rest_map = readline_skipping_spaces(fd);
	if (rest_map != NULL)
	{
		free(rest_map);
		fatal("elements after map");
	}
}

u_int32_t	get_color(int *rgb)
{
	uint8_t	red;
	uint8_t	green;
	uint8_t	blue;

	red = rgb[0];
	green = rgb[1];
	blue = rgb[2];
	return (red << 24 | green << 16 | blue << 8 | 0xFF);
}
