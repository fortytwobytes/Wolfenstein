#include "../includes/srcs.h"

double get_angle_for_direction(char direction)
{
    if (direction == 'N')
        return (M_PI_2);
    if (direction == 'W')
        return (M_PI);
    if (direction == 'S')
        return (3 * M_PI_2);
    return (0);
}

void    init_window(t_var *var)
{
    mlx_set_setting(MLX_STRETCH_IMAGE, false);
    mlx_set_setting(MLX_DECORATED, false);
    var->mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "WolFeinstein 3D", true);
    if (var->mlx == NULL) {
        fatal(mlx_strerror(mlx_errno));
    }
    mlx_set_window_limit(var->mlx, WIN_WIDTH, WIN_HEIGHT, WIN_WIDTH, WIN_HEIGHT);
}

void    init_images(t_var *var)
{
    var->minimap = mlx_new_image(var->mlx, WIN_WIDTH, WIN_HEIGHT);
    if (var->minimap == NULL)
    {
        mlx_close_window(var->mlx);
        fatal(mlx_strerror(mlx_errno));
    }
    var->player.img = mlx_new_image(var->mlx, PLAYER_SIZE, PLAYER_SIZE);
    if (var->player.img == NULL)
    {
        mlx_delete_image(var->mlx, var->minimap);
        mlx_close_window(var->mlx);
        fatal(mlx_strerror(mlx_errno));
    }
    if (mlx_image_to_window(var->mlx, var->minimap, 0, 0) == EOF)
    {
        mlx_delete_image(var->mlx, var->minimap);
        mlx_delete_image(var->mlx, var->player.img);
        mlx_close_window(var->mlx);
        fatal(mlx_strerror(mlx_errno));
    }
    if (mlx_image_to_window(var->mlx, var->player.img, var->player.pos.x, var->player.pos.y) == EOF)
    {
        mlx_delete_image(var->mlx, var->minimap);
        mlx_delete_image(var->mlx, var->player.img);
        mlx_close_window(var->mlx);
        fatal(mlx_strerror(mlx_errno));
    }
    var->player.angle = get_angle_for_direction(var->player.first_view);
    var->player.direction.x = cos(var->player.pos.x);
    var->player.direction.y = sin(var->player.pos.y);
}

