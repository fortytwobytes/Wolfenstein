#include "../../includes/srcs.h"

// checks for angle overflow
double get_angle(double angle)
{
    if (angle > PI_2)
        angle -= PI_2;
    if (angle < 0)
        angle += PI_2;
    return angle;
}

void    adjust_view(t_player *p, int key)
{
    double  angle;

    angle = p->angle;
    if (key == MLX_KEY_LEFT)
        angle -= ROTATE_SPEED;
    else if (key == MLX_KEY_RIGHT)
        angle += ROTATE_SPEED;
    p->angle = get_angle(angle);
    p->direction.x = cos(p->angle) * DIRECTION_LEN;
    p->direction.y = sin(p->angle) * DIRECTION_LEN;
}

void	hooks(void *param) {
    t_var   *var    = param;
    char    **map   = var->map.map;
    int     *xid    = &var->player.img->instances[0].x;
    int     *yid    = &var->player.img->instances[0].y;
    t_player *p     = &var->player;


    if (mlx_is_key_down(var->mlx, MLX_KEY_ESCAPE) == true) {
        mlx_close_window(var->mlx);
    }
    if (mlx_is_key_down(var->mlx, MLX_KEY_A) == true) {
        *xid += p->direction.y;
        *yid -= p->direction.x;
    }
    if (mlx_is_key_down(var->mlx, MLX_KEY_D) == true) {
        *xid -= p->direction.y;
        *yid += p->direction.x;
    }
    if (mlx_is_key_down(var->mlx, MLX_KEY_W) == true) {
        *xid += p->direction.x;
        *yid += p->direction.y;
    }
    if (mlx_is_key_down(var->mlx, MLX_KEY_S) == true) {
        *xid -= p->direction.x;
        *yid -= p->direction.y;
    }
    if (mlx_is_key_down(var->mlx, MLX_KEY_LEFT) == true) {
        adjust_view(p, MLX_KEY_LEFT);
    }
    if (mlx_is_key_down(var->mlx, MLX_KEY_RIGHT) == true) {
        adjust_view(p, MLX_KEY_RIGHT);
    }
    draw_direction(var);
}