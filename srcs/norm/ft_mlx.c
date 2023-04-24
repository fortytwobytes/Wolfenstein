/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relkabou <relkabou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 13:15:10 by relkabou          #+#    #+#             */
/*   Updated: 2023/04/23 13:15:14 by relkabou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/srcs.h"

mlx_t *ft_mlx_init(void)
{
    mlx_t *mlx;

    mlx_set_setting(MLX_STRETCH_IMAGE, false);
    mlx_set_setting(MLX_DECORATED, false);
    mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "cub3D", true);
    if (mlx == NULL)
        fatal(mlx_strerror(mlx_errno));
    mlx_set_window_limit(mlx, WIN_WIDTH, WIN_HEIGHT, WIN_WIDTH, WIN_HEIGHT);
    return (mlx);
}

// REVIEW: we can free the mlx ptr by calling mlx_close_window and mlx_terminate
// but because we still have the ptr accessible no need to.
mlx_image_t *ft_mlx_new_image(mlx_t *mlx, uint32_t width, uint32_t height)
{
    mlx_image_t *image;

    image = mlx_new_image(mlx, width, height);
    if (image == NULL)
        fatal(mlx_strerror(mlx_errno));
    return (image);
}
