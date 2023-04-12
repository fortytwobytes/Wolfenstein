#include "srcs.h"

void	skip_blank_lines(int fd);
bool	is_all_spaces(char *line);
void	skip_till_map(int fd, char *first_map_line);
int    *get_rgb(char *arg);

void	skip_blank_lines(int fd)
{
	char	*line;

	while (true)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (strcmp(line, "\n") == 0 || is_all_spaces(line) == true)
		{
			free(line);
			continue ;
		}
		free(line);
	}
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

void	skip_till_map(int fd, char *first_map_line)
{
	char *line;
	while (true)
	{
		line = get_next_line(fd);
        if (line == NULL)
            break ;
        if (strcmp(line, first_map_line) == 0)
        {
            free(line);
            break ;
        }
		free(line);
	}
}

int    *get_rgb(char *arg)
{
    char    **elements;
    char    *rgb;
    int     i;
    int     *rgb_arr;

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
