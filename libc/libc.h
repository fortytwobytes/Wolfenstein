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

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

char	**ft_split(char *s, char c);
char	*ft_strchr(char *s, int c);
char	*ft_strdup(char *s1);
char	*ft_substr(char *s, unsigned int start, size_t len);
char	*get_next_line(int fd);
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
size_t	ft_strlen(char *s);
void	*ft_calloc(size_t size);
void	fatal(char *message);
void	*ft_memcpy(void *dst, void *src, size_t n);

#endif /* LIBC_H */

