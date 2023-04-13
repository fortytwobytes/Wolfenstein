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
    break;
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

