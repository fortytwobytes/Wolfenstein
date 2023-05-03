#include "../../includes/srcs.h"

void    adjust_view(t_player *p, int key)
{
    double  angle;

    angle = p->angle;
    if (key == MLX_KEY_LEFT)
        angle -= ROTATE_SPEED;
    else
        angle += ROTATE_SPEED;
    p->angle = get_angle(angle);
    p->direction.x = cos(p->angle);
    p->direction.y = sin(p->angle);
}

void    move_up(t_map map, t_player *p)
{
    p->next_pos.x = *p->x_pixel + p->direction.x * SPEED;
    p->next_pos.y = *p->y_pixel + p->direction.y * SPEED;
    update_player_position(map, p);
}

void    move_down(t_map map, t_player *p)
{
    p->next_pos.x = *p->x_pixel - p->direction.x * SPEED;
    p->next_pos.y = *p->y_pixel - p->direction.y * SPEED;
    update_player_position(map, p);
}

void    move_left(t_map map, t_player *p)
{
    p->next_pos.x = *p->x_pixel - cos (p->direction.x * M_PI) * SPEED;
    p->next_pos.y = *p->y_pixel - sin (p->direction.y * M_PI) * SPEED;
    update_player_position(map, p);
}

void    move_right(t_map map, t_player *p)
{
    p->next_pos.x = *p->x_pixel + cos (p->direction.x * M_PI) * SPEED;
    p->next_pos.y = *p->y_pixel + sin (p->direction.y * M_PI) * SPEED;
    update_player_position(map, p);
}
