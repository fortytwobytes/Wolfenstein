#include "../../includes/srcs.h"

// checks for angle overflow
double getAngle(double angle)
{
    double _2pi;

    _2pi = M_PI * 2.0;

    if (angle > _2pi)
        angle -= _2pi;
    if (angle < 0)
        angle += _2pi;
    return angle;
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
        *xid += p->direction.y * SPEED;
        *yid -= p->direction.x * SPEED;
    }
    if (mlx_is_key_down(var->mlx, MLX_KEY_D) == true) {
        *xid -= p->direction.y * SPEED;
        *yid += p->direction.x * SPEED;
    }
    if (mlx_is_key_down(var->mlx, MLX_KEY_W) == true) {
        *xid += p->direction.x * SPEED;
        *yid += p->direction.y * SPEED;
    }
    if (mlx_is_key_down(var->mlx, MLX_KEY_S) == true) {
        *xid -= p->direction.x * SPEED;
        *yid -= p->direction.y * SPEED;
    }
    if (mlx_is_key_down(var->mlx, MLX_KEY_LEFT) == true) {
        p->angle += ROTATE_SPEED;
        p->angle = getAngle(p->angle);
        p->direction.x = +cos(p->angle);
        p->direction.y = -sin(p->angle);
    }
    if (mlx_is_key_down(var->mlx, MLX_KEY_RIGHT) == true) {
        p->angle -= ROTATE_SPEED;
        p->angle = getAngle(p->angle);
        p->direction.x = +cos(p->angle);
        p->direction.y = -sin(p->angle);
    }
}