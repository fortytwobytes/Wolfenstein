#include "libc.h"

char	*strjoin(char *str1, char *str2)
{
	char	*buffer;
	size_t	len1;
	size_t	len2;

	len1 = strlen(str1);
	len2 = strlen(str2);
	buffer = ft_calloc(len1 + len2 + 1);
	memcpy(buffer, str1, len1);
    memcpy(buffer + len1, str2, len2 + 1);
	return buffer;
}

