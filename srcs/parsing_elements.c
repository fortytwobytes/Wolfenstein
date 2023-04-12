#include "srcs.h"

// change the NULL with the mlx pointer
// to optimize later
static void	fill_map_struct(t_map *map, char *element, char *arg)
{
	if (!strcmp(element, "NO"))
	{
		map->NO_path = arg;
		is_texture_valid(NULL, arg);
	}
	else if (!strcmp(element, "SO"))
	{
		map->SO_path = arg;
		is_texture_valid(NULL, arg);
	}
	else if (!strcmp(element, "WE"))
	{
		map->WE_path = arg;
		is_texture_valid(NULL, arg);
	}
	else if (!strcmp(element, "EA"))
	{
		map->EA_path = arg;
		is_texture_valid(NULL, arg);
	}
	else if (!strcmp(element, "S"))
	{
		map->SO_path = arg;
		is_texture_valid(NULL, arg);
	}
	else if (!strcmp(element, "F"))
	{
		map->F_color = get_rgb(arg);
	}
	else if (!strcmp(element, "C"))
	{
		map->C_color = get_rgb(arg);
	}
}

void	parse_elements(int fd, t_map *map)
{
	char	**elements;
	char	*line;
	int		i;

	i = -1;
	while (++i < NBROF_ELEMENTS)
	{
		skip_blank_lines(fd);
		line = get_next_line(fd);
		elements = ft_split(line, SPACES);
		if (ft_split_len(elements) != 2)
			return (ft_free_split(elements), free(line), fatal("error"));
		fill_map_struct(map, elements[0], elements[1]);
		free(line);
		ft_free_split(elements);
	}
	skip_blank_lines(fd);
    get_map_dimentions(fd, map);
}