/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strjoin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relkabou <relkabou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 17:42:11 by relkabou          #+#    #+#             */
/*   Updated: 2023/05/13 17:42:11 by relkabou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libc.h"

char	*strjoin(char *str1, char *str2)
{
	char	*buffer;
	size_t	len1;
	size_t	len2;

	len1 = ft_strlen(str1);
	len2 = ft_strlen(str2);
	buffer = ft_calloc(len1 + len2 + 1);
	ft_memcpy(buffer, str1, len1);
	ft_memcpy(buffer + len1, str2, len2 + 1);
	return (buffer);
}
