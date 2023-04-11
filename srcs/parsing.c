#include "srcs.h"

bool	is_filename_valid(char *filename)
{
	int		extension_len;
	int		filename_len;
	char	*extension;

	extension = ".cub";
	filename_len = strlen(filename);
	extension_len = strlen(extension);
	if (filename_len <= extension_len)
		return (false);
	filename += filename_len - extension_len;
	if (strcmp(filename, extension))
		return (false);
	return (true);
}

void    ft_free_bins(char   **elements)
{
    int i;

    i = -1;
    while (elements[++i])
        free(elements[i]);
    free(elements);
}

int ft_count_bins(char  **elements)
{
    int i;

    i = -1;
    while (elements[++i])
        ;
    return (i);
}

int ft_check_rgb(char *rgb)
{
    int i;
    int j;
    char **rgb_elements;


    rgb_elements = ft_split(rgb, ',');
    i = -1;

    if (ft_count_bins(rgb_elements) != 3)
        return (ft_free_bins(rgb_elements), -1);
    while (rgb_elements[++i])
    {
        j = -1;
        if (ft_strlen(rgb_elements[i]) > 3)
            return (ft_free_bins(rgb_elements), -1);
        while (rgb_elements[i][++j])
            if (rgb_elements[i][j] < 0 || rgb_elements[i][j] > 9)
                return (ft_free_bins(rgb_elements), -1);
        if (ft_atoi(rgb_elements[i]) > 255)
            return (ft_free_bins(rgb_elements), -1);
    }
    return (0);
}

int ft_is_typeof_element(char *type)
{
    int what_type;

    what_type = -1;
    if (!ft_strncmp(type, "NO", 2) || !ft_strncmp(type, "SO", 2) ||
            !ft_strncmp(type, "WE", 2) || !ft_strncmp(type, "EA", 2))
        what_type = 0;
    if (!ft_strncmp(type, "F", 1) || !ft_strncmp(type, "C", 1))
        what_type = 1;
    return (what_type);
}

int ft_is_argof_element(char *element, char *arg)
{
    if (ft_is_typeof_element(element))
        return (ft_check_rgb(arg));
    return (0);
}

void ft_check_type_of_elements(int fd)
{
    char    **elements;
    char    *map_line;
    char    *tmp;

    while (1)
    {
        tmp = get_next_line(fd);
        map_line = ft_strtrim(tmp, " "); //remove it after
        elements = ft_split(map_line, ' ');
        if (ft_count_bins(elements) != 2)
        {
            ft_free_bins(elements);
            free(map_line);
            return (write(1, "ERROR\n", 6), exit(0));
        }
        if (ft_is_typeof_element(elements[0]) == -1 || 
            ft_is_argof_element(elements[0], elements[1]))
        {
            ft_free_bins(elements);
            free(map_line);
            return (write(1, "ERROR\n", 6), exit(0));
        }
        free(tmp);
        free(map_line);
        ft_free_bins(elements);
    }
}

void parse_map(char *path)
{
    int     fd;

    fd = open(path, O_RDONLY);
    ft_check_type_of_elements(fd);
}

