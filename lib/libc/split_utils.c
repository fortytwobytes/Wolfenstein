/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relkabou <relkabou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 01:40:27 by relkabou          #+#    #+#             */
/*   Updated: 2023/04/18 01:40:27 by relkabou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libc.h"

void	ft_free_split(char **split)
{
	int	i;

	i = -1;
	while (split[++i])
		free(split[i]);
	free(split);
}

int	ft_split_len(char **elements)
{
	int	i;

	i = -1;
	while (elements[++i])
		;
	return (i);
}
