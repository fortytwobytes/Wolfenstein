#include "srcs.h"



void    parse_map(int fd, t_map *map)
{
    char    *line;
    int     i;

    i = -1;
    skip_till_map(fd, map->first_map_line);
    map->map = ft_calloc(sizeof(char *) * (map->max_height + 1));
    while (++i < map->max_height)
    {
        line = get_next_line(fd);
        map->map[i] = ft_calloc(sizeof(char) * (map->max_width + 1));
        memset(map->map[i], ' ', map->max_width);
        map->map[i] = ft_memcpy(map->map[i], line, ft_strlen(line));
        free(line);
    }
    for (int i = 0; i < map->max_height; i++)
        puts(map->map[i]);
}