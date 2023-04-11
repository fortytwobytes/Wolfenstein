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

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

char	**ft_split(char *s, char c);
char	*ft_strchr(char *s, int c);
char	*ft_strdup(char *s1);
char	*ft_substr(char *s, unsigned int start, size_t len);
char	*get_next_line(int fd);
char	*strjoin(char *str1, char *str2);
size_t	ft_strlen(char *s);
void	*ft_calloc(size_t size);
void	fatal(char *message);
void	*ft_memcpy(void *dst, void *src, size_t n);

#endif /* LIBC_H */

