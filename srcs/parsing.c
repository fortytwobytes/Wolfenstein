#include "srcs.h"

bool	is_all_num(char **elements);
bool	is_all_spaces(char *line);
int		*get_rgb(char *arg);
void	fill_map_struct(t_var *var, char *element, char *arg);
void	is_texture_valid(void *mlx, char *path);
void	parse_elements(t_var *var, char *filename);
void	parsing(t_var *var, char *cub_filename);
char	*readline_skipping_spaces(int fd);
void	get_map_dimentions(int fd, t_map *map);
void	init_map(t_map *map);
void	parse_map(t_var *var, char *path);
void	fill_2d_map(int fd, t_map *map);
void	skip_till_first_map_line(int fd, t_map *map);

void	parsing(t_var *var, char *cub_filename)
{
	init_map(&var->map);
	parse_elements(var, cub_filename);
	parse_map(var, cub_filename);
}

void	init_map(t_map *map)
{
	map->no_path = NULL;
	map->so_path = NULL;
	map->ea_path = NULL;
	map->we_path = NULL;
	map->c_color = NULL;
	map->f_color = NULL;
	map->max_height = 1;
}

void	parse_elements(t_var *var, char *filename)
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

void	parse_map(t_var *var, char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	skip_till_first_map_line(fd, &var->map);
	fill_2d_map(fd, &var->map);
	close(fd);
}

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

void	fill_2d_map(int fd, t_map *map)
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
	for (int i = 0; map->map[i]; i++)
	{
		printf("%s\n", map->map[i]);
	}
}

char	*get_texture(t_var *var, char *path)
{
	int		img_height;
	int		img_width;
	void	*img;

	img = mlx_xpm_file_to_image(var->mlx.mlx, path, &img_width, &img_height);
	if (img == NULL)
		fatal("invalid texture");
	// free(img);
	mlx_destroy_image(var->mlx.mlx, img);
	return (path);
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

void	fill_map_struct(t_var *var, char *element, char *arg)
{
	if (!strcmp(element, "NO") && var->map.no_path == NULL)
		var->map.no_path = get_texture(var, arg);
	else if (!strcmp(element, "SO") && var->map.so_path == NULL)
		var->map.so_path = get_texture(var, arg);
	else if (!strcmp(element, "WE") && var->map.we_path == NULL)
		var->map.we_path = get_texture(var, arg);
	else if (!strcmp(element, "EA") && var->map.ea_path == NULL)
		var->map.ea_path = get_texture(var, arg);
	else if (!strcmp(element, "F") && var->map.f_color == NULL)
		var->map.f_color = get_rgb(arg);
	else if (!strcmp(element, "C") && var->map.c_color == NULL)
		var->map.c_color = get_rgb(arg);
	else
		fatal("duplicated or invalid element");
}

int	*get_rgb(char *arg)
{
	char	**elements;
	char	*rgb;
	int		i;
	int		*rgb_arr;

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
	return (rgb_arr);
}

bool	is_all_spaces(char *line)
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

/*
TODO: check for invalid map conditions
* all zeros should be cerounded by ones
* check if there's another char in the map rather than 'NEWS01' and spaces
* check if the map is closed by ones
*/
void	get_map_dimentions(int fd, t_map *map)
{
	char	*line;
	int		line_len;

	map->max_width = ft_strlen(map->first_map_line);
	while (true)
	{
		line = get_next_line(fd);
		if (line == NULL || strcmp(line, "\n") == 0)
			break ;
		line_len = ft_strlen(line);
		if (line_len > map->max_width)
			map->max_width = line_len;
		map->max_height++;
		free(line);
	}
}

bool	is_all_num(char **elements)
{
	int i;
	int j;

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