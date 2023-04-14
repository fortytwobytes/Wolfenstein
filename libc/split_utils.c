#include "libc.h"

int		ft_split_len(char **elements);
void	ft_free_split(char **split);

void	ft_free_split(char **split)
{
	int	i;

	i = -1;
	while (split[++i])
		free(split[i]);
	free(split);
}

int	ft_split_len(char **elements)
{
	int	i;

	i = -1;
	while (elements[++i])
		;
	return (i);
}