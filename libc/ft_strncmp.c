/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouakch <onouakch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 16:29:55 by onouakch          #+#    #+#             */
/*   Updated: 2023/04/11 02:48:09 by onouakch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libc.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*_s1;
	unsigned char	*_s2;

	_s1 = (unsigned char *)s1;
	_s2 = (unsigned char *)s2;
	i = 0;
	if (n == 0)
		return (0);
	while ((_s1[i] == _s2[i]) && (_s1[i] != '\0'
			&& _s2[i] != '\0') && i < n - 1)
		i++;
	return (_s1[i] - _s2[i]);
}
