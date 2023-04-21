/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouakch <onouakch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 20:33:19 by onouakch          #+#    #+#             */
/*   Updated: 2023/04/20 14:25:08 by relkabou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/srcs.h"

static bool	is_all_num(char **elements)
{
	int	i;
	int	j;

	i = -1;
	while (elements[++i])
	{
		j = -1;
		while (elements[i][++j])
		{
			if (elements[i][j] < '0' || elements[i][j] > '9')
				return (false);
		}
	}
	return (true);
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

char	*readline_skipping_spaces(int fd)
{
	char	*line;

	while (true)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (is_all_spaces(line) == true || strcmp(line, "\n") == 0)
		{
			free(line);
			continue ;
		}
		return (line);
	}
	return (NULL);
}

// TODO: refactor this function
static u_int32_t	get_rgb(char *arg)
{
	int		i;
	char	*rgb;
	int		*rgb_arr;
	char	**elements;
	u_int32_t color;

	rgb_arr = ft_calloc(sizeof(int) * 3);
	rgb = ft_strtrim(arg, "()");
	elements = ft_split(rgb, ",");
	if (ft_split_len(elements) != 3)
		fatal("invalid rgb");
	is_all_num(elements);
	i = 0;
	while (elements[i])
	{
		if (ft_strlen(elements[i]) > 3)
			fatal("invalid rgb");
		rgb_arr[i] = ft_atoi(elements[i]);
		if (rgb_arr[i] > 255 || rgb_arr[i] < 0)
			fatal("invalid rgb");
		i++;
	}
	free(rgb);
	ft_free_split(elements);
	color = get_color(rgb_arr);
	free(rgb_arr);
	return (color);
}

// TODO: add another check for the colors the old is redundant
void	fill_map_struct(t_var *var, char *element, char *arg)
{
	if (!strcmp(element, "NO") && var->map.no_image == NULL)
		var->map.no_image = get_texture(var, arg);
	else if (!strcmp(element, "SO") && var->map.so_image == NULL)
		var->map.so_image = get_texture(var, arg);
	else if (!strcmp(element, "WE") && var->map.we_image == NULL)
		var->map.we_image = get_texture(var, arg);
	else if (!strcmp(element, "EA") && var->map.ea_image == NULL)
		var->map.ea_image = get_texture(var, arg);
	else if (!strcmp(element, "F") /*&& var->map.f_color == NULL */)
		var->map.f_color = get_rgb(arg);
	else if (!strcmp(element, "C") /* && var->map.c_color == NULL */)
		var->map.c_color = get_rgb(arg);
	else
		fatal("duplicated or invalid element");
}
