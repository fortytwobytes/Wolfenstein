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
# include "get_next_line.h"

void	fatal(char *message);
void	*ft_calloc(size_t size);
char	*strjoin(char *str1, char *str2);
int	    ft_atoi(const char *str);
char	**ft_split(char const *s, char c);
size_t	ft_strlen(const char *str);
int     ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_strrchr(const char *s, int c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft__strlen(const char *str);
char	*ft__strjoin(char **s1, char **s2);
char	*ft_strchr(const char *s, int c);
char	*ft_truncate_left(char *str);
char	*ft_truncate_right(char **str);
char	*ft_read_line(int fd, char *reserve);
char	*get_next_line(int fd);

#endif /* LIBC_H */

