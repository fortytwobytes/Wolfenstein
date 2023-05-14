/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fatal.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relkabou <relkabou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 17:42:11 by relkabou          #+#    #+#             */
/*   Updated: 2023/05/13 17:42:11 by relkabou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libc.h"

// TODO: void the message when submitting
void	fatal(const char *message)
{
	write(2, "Error\n", 6);
	while (*message)
		write(2, message++, 1);
	write(2, "\n", 1);
	exit(EXIT_FAILURE);
}
