#include "../../includes/srcs.h"

void	hooks(void *param)
{
    t_var *var = param;
    t_player *p = &var->player;
    t_map map = var->map;

    if (mlx_is_key_down(var->mlx, MLX_KEY_ESCAPE)) // ↑
        exit(1); // to change later
    if (mlx_is_key_down(var->mlx, MLX_KEY_W)) // ↑
        move_up(map, p);
    if (mlx_is_key_down(var->mlx, MLX_KEY_S)) // ↓
        move_down(map, p);
    if (mlx_is_key_down(var->mlx, MLX_KEY_A)) // ←
        move_left(map, p);
    if (mlx_is_key_down(var->mlx, MLX_KEY_D)) // →
        move_right(map, p);
    if (mlx_is_key_down(var->mlx, MLX_KEY_LEFT)) // ↺
        adjust_view(p, MLX_KEY_LEFT);
    if (mlx_is_key_down(var->mlx, MLX_KEY_RIGHT)) // ↻
        adjust_view(p, MLX_KEY_RIGHT);
    update_player_position(map, p);
}

// checks for angle overflow
double get_angle(double angle)
{
    if (angle > PI_2)
        angle -= PI_2;
    if (angle < 0)
        angle += PI_2;
    return angle;
}

// update the pixels, map, direction, view, casts
void   update_player_position(t_map map, t_player *p)
{
    int center_x;
    int center_y;

    center_x = ((int)p->next_pos.x + PLAYER_SIZE / 2) / CUBE_SIZE;
    center_y = ((int)p->next_pos.y + PLAYER_SIZE / 2) / CUBE_SIZE;
    if (map.map[center_x][center_y] == '1')
        return ;
    *p->x_pixel = (int) p->next_pos.x;
    *p->y_pixel = (int) p->next_pos.y;
    p->x_map = (int) *p->x_pixel / CUBE_SIZE;
    p->y_map = (int) *p->y_pixel / CUBE_SIZE;
}
