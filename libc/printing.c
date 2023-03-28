#include "libc.h"

void	fatal(char *message)
{
	write(2, "fatal: ", 7);
	while (*message)
		write(2, message++, 1);
	write(2, "\n", 1);
	exit(EXIT_FAILURE);
}

