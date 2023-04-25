/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relkabou <relkabou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 08:33:34 by relkabou          #+#    #+#             */
/*   Updated: 2023/04/24 08:33:34 by relkabou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libc.h"

void	*ft_calloc(size_t size)
{
	size_t	i;
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

