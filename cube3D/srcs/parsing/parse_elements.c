/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouakch <onouakch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 20:33:19 by onouakch          #+#    #+#             */
/*   Updated: 2023/05/19 17:21:08 by onouakch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/srcs.h"

static u_int32_t	get_rgb(char *arg);
static bool			check_commas(char *str);
static bool			is_all_num(char **elements);

void	fill_map_struct(t_var *var, char *element, char *arg)
{
	if (!ft_strcmp(element, "NO") && var->map.no_image == NULL)
		var->map.no_image = get_texture(var, arg);
	else if (!ft_strcmp(element, "SO") && var->map.so_image == NULL)
		var->map.so_image = get_texture(var, arg);
	else if (!ft_strcmp(element, "WE") && var->map.we_image == NULL)
		var->map.we_image = get_texture(var, arg);
	else if (!ft_strcmp(element, "EA") && var->map.ea_image == NULL)
		var->map.ea_image = get_texture(var, arg);
	else if (!ft_strcmp(element, "F") && var->map.f_color == -1)
		var->map.f_color = get_rgb(arg);
	else if (!ft_strcmp(element, "C") && var->map.c_color == -1)
		var->map.c_color = get_rgb(arg);
	else
		fatal("duplicated or invalid element");
}

static u_int32_t	get_rgb(char *arg)
{
	int			i;
	int			*rgb_arr;
	char		**elements;
	u_int32_t	color;

	i = -1;
	rgb_arr = ft_calloc(sizeof(int) * 3);
	elements = ft_split(arg, ",");
	if (ft_split_len(elements) != 3 || is_all_num(elements) == false
		|| check_commas(arg) == false)
		fatal("invalid rgb");
	while (elements[++i])
	{
		if (ft_strlen(elements[i]) > 3)
			fatal("invalid rgb");
		rgb_arr[i] = ft_atoi(elements[i]);
		if (rgb_arr[i] > 255 || rgb_arr[i] < 0)
			fatal("invalid rgb");
	}
	color = get_color(rgb_arr);
	ft_free_split(elements);
	free(rgb_arr);
	return (color);
}

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

static bool	check_commas(char *str)
{
	int	i;
	int	nbrof_commas;

	i = -1;
	nbrof_commas = 0;
	if (str == NULL)
		return (false);
	while (str[++i])
	{
		if (str[i] == ',')
			nbrof_commas++;
	}
	return (nbrof_commas == 2);
}
