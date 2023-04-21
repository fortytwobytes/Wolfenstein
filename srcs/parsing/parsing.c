/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouakch <onouakch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 15:53:04 by onouakch          #+#    #+#             */
/*   Updated: 2023/04/19 21:10:37 by onouakch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/srcs.h"

// TODO: find another way to check for colors
// cause they are no longer a pointers
// maybe we can use a value that's bigger than u_int32_t
static void	init_map(t_var *var)
{
	var->map.no_image = NULL;
	var->map.so_image = NULL;
	var->map.ea_image = NULL;
	var->map.we_image = NULL;
//	var->map.c_color = NULL;
//	var->map.f_color = NULL;
	var->map.max_height = 1;
	var->player.first_view = '\0';
}

static void	fill_2d_map(int fd, t_map *map)
{
	char	*line;
	int		i;

	i = 0;
	line = ft_strdup(map->first_map_line);
	map->map = ft_calloc(sizeof(char *) * (map->max_height + 1));
	while (true)
	{
		map->map[i] = ft_calloc(sizeof(char) * (map->max_width + 1));
		memset(map->map[i], ' ', map->max_width);
		ft_memcpy(map->map[i], line, ft_strlen(line) - 1);
		free(line);
		line = readline_skipping_spaces(fd);
		if (line == NULL)
			break ;
		i++;
	}
}

static void	parse_map(t_var *var, char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	skip_till_first_map_line(fd, &var->map);
	fill_2d_map(fd, &var->map);
	ft_check_map(var);
	close(fd);
}

static void	parse_elements(t_var *var, char *filename)
{
	int		i;
	int		fd;
	char	**elements;
	char	*line;

	i = -1;
	fd = open(filename, O_RDONLY);
	if (fd == EOF)
		fatal("can't open the map file");
	while (++i < NBROF_ELEMENTS)
	{
		line = readline_skipping_spaces(fd);
		if (line == NULL)
			break ;
		elements = ft_split(line, SPACES);
		if (ft_split_len(elements) != 2)
			fatal("invalid map elements");
		fill_map_struct(var, elements[0], elements[1]);
		free(line);
		ft_free_split(elements);
	}
	var->map.first_map_line = readline_skipping_spaces(fd);
	get_map_dimentions(fd, &var->map);
	close(fd);
}

void	parsing(t_var *var, char *cub_filename)
{
	init_map(var);
	parse_elements(var, cub_filename);
	parse_map(var, cub_filename);
}
