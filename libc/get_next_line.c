/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouakch <onouakch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 20:05:17 by onouakch          #+#    #+#             */
/*   Updated: 2023/04/11 03:01:27 by onouakch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_read_line(int fd, char *reserve)
{
	char	*buff;
	int		check;

	buff = malloc((1 + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	check = 1;
	while (check != 0 && ft_strchr(reserve, '\n') == NULL)
	{
		check = read(fd, buff, 1);
		if (check == -1)
			return (free(buff), NULL);
		buff[check] = '\0';
		reserve = ft__strjoin(&reserve, &buff);
	}
	free(buff);
	return (reserve);
}

char	*get_next_line(int fd)
{
	static char	*reserve = NULL;
	char		*result;

	if (fd < 0)
		return (0);
	reserve = ft_read_line(fd, reserve);
	if (!reserve)
		return (NULL);
	result = ft_truncate_left(reserve);
	reserve = ft_truncate_right(&reserve);
	return (result);
}    
