/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouakch <onouakch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 17:00:40 by onouakch          #+#    #+#             */
/*   Updated: 2023/04/24 08:34:54 by relkabou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libc.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	ls1;

	if (!s1 || !set)
		return (NULL);
	while (*s1 && ft_strchr(set, *s1) != NULL)
		s1++;
	ls1 = ft_strlen(s1) - 1;
	while (ft_strrchr(set, *(s1 + ls1)) != NULL)
		ls1--;
	return (ft_substr(s1, 0, ls1 + 1));
}
