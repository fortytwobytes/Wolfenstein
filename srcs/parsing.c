#include "srcs.h"

bool	is_all_num(char **elements);
bool	is_all_spaces(char *line);
int		*get_rgb(char *arg);
void	fill_map_struct(t_var *var, char *element, char *arg);
void	is_texture_valid(void *mlx, char *path);
void	parse_elements(t_var *var, char *filename);
void	parsing(t_var *var, char *cub_filename);
char	*skip_blank_lines(int fd);
void    get_map_dimentions(int fd, t_map *map);

void	parsing(t_var *var, char *cub_filename)
{
	parse_elements(var, cub_filename);
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
		line = skip_blank_lines(fd);
        printf("line %s", line);
		if (line == NULL)
			break ;
		elements = ft_split(line, SPACES);
		if (ft_split_len(elements) != 2)
			fatal("invalid map elements");
		fill_map_struct(var, elements[0], elements[1]);
		free(line);
		ft_free_split(elements);
	}
	var->map.first_map_line = skip_blank_lines(fd);
	close(fd);
}

void	is_texture_valid(void *mlx, char *path)
{
	int		img_height;
	int		img_width;
	void	*img;

    printf("-->|%s|<--", path);
    printf("%p\n", mlx);
	img = mlx_xpm_file_to_image(mlx, "./textures/wall.xpm", &img_width, &img_height);
	if (img == NULL)
		fatal("invalid texture");
	free(img);
}

char	*skip_blank_lines(int fd)
{
	char	*line;

	while (true)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (is_all_spaces(line) == true || strcmp(line, "\n") == 0) // maybe there's an error in this code cause of the first check
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
	if (!strcmp(element, "NO"))
	{
		var->map.NO_path = arg;
		is_texture_valid(var->mlx.mlx, arg);
	}
	else if (!strcmp(element, "SO"))
	{
		var->map.SO_path = arg;
		is_texture_valid(var->mlx.mlx, arg);
	}
	else if (!strcmp(element, "WE"))
	{
		var->map.WE_path = arg;
		is_texture_valid(var->mlx.mlx, arg);
	}
	else if (!strcmp(element, "EA"))
	{
		var->map.EA_path = arg;
		is_texture_valid(var->mlx.mlx, arg);
	}
	else if (!strcmp(element, "S"))
	{
		var->map.SO_path = arg;
		is_texture_valid(var->mlx.mlx, arg);
	}
	else if (!strcmp(element, "F"))
	{
		var->map.F_color = get_rgb(arg);
	}
	else if (!strcmp(element, "C"))
	{
		var->map.C_color = get_rgb(arg);
	}
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
		if (line[i] != ' ' && line[i] != '\t')
			return (false);
	return (true);
}

void    get_map_dimentions(int fd, t_map *map)
{
    char    *line;
    int     line_len;

    map->max_width = 0;
    map->max_height = 0;
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