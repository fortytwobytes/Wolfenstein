#include "../../includes/srcs.h"

void	free_split(char **split)
{
	int i = -1;
	while (split[++i])
		free(split[i]);
	free(split);
}

t_vect_i get_player_xy_position(char **realMap)
{
	int x = -1;
	while (realMap[++x]) {
		int y = -1;
		while (realMap[x][++y]) {
			if (strchr("NEWSP", realMap[x][y]))
				return ((t_vect_i) {x, y});
		}
	}
	fatal("No player found");
	return ((t_vect_i) {-1, -1});
}

t_vect_f get_first_player_direction(char direction)
{
	t_vect_f dir;

	if (direction == 'N')
		dir = (t_vect_f){0, -1};
	else if (direction == 'S')
		dir = (t_vect_f){0, 1};
	else if (direction == 'E')
		dir = (t_vect_f){1, 0};
	else if (direction == 'W')
		dir = (t_vect_f){-1, 0};
	return (dir);
}
