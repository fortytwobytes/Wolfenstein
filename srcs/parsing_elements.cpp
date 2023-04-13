#include "srcs.h"

// change the NULL with the mlx pointer
// to optimize later
static void	fill_map_struct(t_var *var, char *element, char *arg)
{
	if (!strcmp(element, "NO"))
	{
		var->map->NO_path = arg;
		is_texture_valid(var->mlx->mlx, arg);
	}
	else if (!strcmp(element, "SO"))
	{
		var->map->SO_path = arg;
		is_texture_valid(var->mlx->mlx, arg);
	}
	else if (!strcmp(element, "WE"))
	{
		var->map->WE_path = arg;
		is_texture_valid(var->mlx->mlx, arg);
	}
	else if (!strcmp(element, "EA"))
	{
		var->map->EA_path = arg;
		is_texture_valid(var->mlx->mlx, arg);
	}
	else if (!strcmp(element, "S"))
	{
		var->map->SO_path = arg;
		is_texture_valid(var->mlx->mlx, arg);
	}
	else if (!strcmp(element, "F"))
	{
		var->map->F_color = get_rgb(arg);
	}
	else if (!strcmp(element, "C"))
	{
		var->map->C_color = get_rgb(arg);
	}
}

void	parse_elements(int fd, t_var *var)
{
	char	**elements;
	char	*line;
	int		i;

	i = -1;
	while (++i < NBROF_ELEMENTS)
	{
		skip_blank_lines(fd);
		line = get_next_line(fd);
		if (!line)
			break ;
		elements = ft_split(line, SPACES);
		if (ft_split_len(elements) != 2)
			return (ft_free_split(elements), free(line), fatal("error"));
		fill_map_struct(var->map, elements[0], elements[1]);
		free(line);
		ft_free_split(elements);
	}
	skip_blank_lines(fd);
	get_map_dimentions(fd, var->map);
}
