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
# include "libc.h"
# include <limits.h>
#include <time.h>

char	**ft_split(char *str, char *charset);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(char *s1);
char	*ft_strdup(char *str);
char	*ft_strrchr(const char *s, int c);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*get_next_line(int fd);
char	*strjoin(char *str1, char *str2);
int		ft_atoi(const char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int     ft_split_len(char **elements);
int 	ft_strcmp(const char *s1, const char *s2);
size_t	ft_strlen(const char *s);
void	*ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t size);
void	*ft_memcpy(void *dst, void *src, size_t n);
void	*ft_memset(void *b, int c, size_t len);
void	fatal(const char *message);
void	ft_free_split(char **split);
void	ft_free_split(char **split);

#endif /* LIBC_H */
