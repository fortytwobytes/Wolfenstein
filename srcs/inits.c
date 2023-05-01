#include "../includes/srcs.h"

static void init_player(t_var *var, t_player *p);
static double get_angle_for_direction(char direction);

void    init_window(t_var *var)
{
    mlx_set_setting(MLX_STRETCH_IMAGE, false);
//    mlx_set_setting(MLX_DECORATED, false);
    var->mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "WolFeinstein 3D", true);
    if (var->mlx == NULL) {
        fatal(mlx_strerror(mlx_errno));
    }
    mlx_set_window_limit(var->mlx, WIN_WIDTH, WIN_HEIGHT, WIN_WIDTH, WIN_HEIGHT);
}


void    init_images(t_var *var)
{
    var->minimap = mlx_new_image(var->mlx, WIN_WIDTH, WIN_HEIGHT);
    var->scene3d = mlx_new_image(var->mlx, WIN_WIDTH, WIN_HEIGHT);
    var->player.img = mlx_new_image(var->mlx, PLAYER_SIZE, PLAYER_SIZE);
    var->rays = mlx_new_image(var->mlx, WIN_WIDTH, WIN_HEIGHT);
    if (!var->minimap || !var->player.img || !var->rays)
        fatal(mlx_strerror(mlx_errno));
    if (mlx_image_to_window(var->mlx, var->minimap, 0, 0) == EOF)
        fatal(mlx_strerror(mlx_errno));
    if (mlx_image_to_window(var->mlx, var->player.img, var->player.first_pos.x, var->player.first_pos.y) == EOF)
        fatal(mlx_strerror(mlx_errno));
    init_player(var, &var->player);
}

static void init_player(t_var *var, t_player *p)
{
    p->angle = get_angle_for_direction(var->player.first_view);
    p->direction.x = cos(p->angle);
    p->direction.y = sin(p->angle);
    p->x_pixel = &p->img->instances[0].x;
    p->y_pixel = &p->img->instances[0].y;
    p->x_map = *var->player.x_pixel / CUBE_SIZE;
    p->y_map = *var->player.y_pixel / CUBE_SIZE;
    p->next_pos.x = *p->x_pixel + p->direction.x * SPEED;
    p->next_pos.y = *p->y_pixel + p->direction.y * SPEED;
}

static double get_angle_for_direction(char direction)
{
    if (direction == 'N')
        return (3 * M_PI_2);
    if (direction == 'W')
        return (M_PI);
    if (direction == 'S')
        return (M_PI_2);
    return (0);
}
