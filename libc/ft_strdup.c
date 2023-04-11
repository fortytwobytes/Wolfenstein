/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relkabou <relkabou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 17:50:24 by relkabou          #+#    #+#             */
/*   Updated: 2023/04/11 17:50:25 by relkabou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libc.h"

char	*ft_strdup(char *str)
{
	char	*buffer;
	size_t	str_len;

	str_len = ft_strlen(str);
	buffer = ft_calloc(sizeof(char) * (str_len + 1));
	ft_memcpy(buffer, str, str_len);
	return (buffer);
}
