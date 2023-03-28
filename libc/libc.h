#ifndef LIBC_H
# define LIBC_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include <stdbool.h>
# include <assert.h>

void	*ft_calloc(size_t size);
void	fatal(char *message);

#endif /* LIBC_H */

