#include "../includes/srcs.h"

static void init_player(t_var *var, t_player *p);
static double get_angle_for_direction(char direction);

void    init_window(t_var *var)
{
    mlx_set_setting(MLX_STRETCH_IMAGE, false);
    mlx_set_setting(MLX_DECORATED, false);
    var->mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "WolFeinstein 3D", true);
    if (var->mlx == NULL) {
        fatal(mlx_strerror(mlx_errno));
    }
    mlx_set_window_limit(var->mlx, WIN_WIDTH, WIN_HEIGHT, WIN_WIDTH, WIN_HEIGHT);
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
