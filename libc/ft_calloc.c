#include "libc.h"

void	*ft_calloc(size_t size)
{
	int		i;
	char	*buffer;

	i = 0;
	buffer = malloc(size);
	if (!buffer)
		fatal("can't allocate memory");
	while (i < size)
	{
		buffer[i] = 0;
		i++;
	}
	return ((void *)buffer);
}

