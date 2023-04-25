#include "../../includes/srcs.h"

void    move_up(t_map map, t_player *p)
{
    int next_x;
    int next_y;

    next_x = (int)(*p->x_pos + (p->direction.x * SPEED));
    next_y = (int)(*p->y_pos + (p->direction.y * SPEED));
    // tmp protection for the map size

    if (next_x >= map.max_width * CUBE_SIZE || next_y >= map.max_height * CUBE_SIZE)
        fatal("over the map");
    printf("next_x: %d, next_y: %d)\n", next_x, next_y);
    if (map.map[next_x / CUBE_SIZE][next_y / CUBE_SIZE] == '1')
        return ;
    *p->x_pos = next_x;
    *p->y_pos = next_y;
}

void    move_down(t_map map, t_player *p)
{
    int next_x;
    int next_y;

    next_x = (int)(*p->x_pos - (p->direction.x * SPEED));
    next_y = (int)(*p->y_pos - (p->direction.y * SPEED));
    // tmp protection for the map size
    if (next_x >= map.max_width * CUBE_SIZE || next_y >= map.max_height * CUBE_SIZE)
        fatal("over the map");
    printf("next_x: %d, next_y: %d)\n", next_x, next_y);
    if (map.map[next_x / CUBE_SIZE][next_y / CUBE_SIZE] == '1')
        return ;
    *p->x_pos = next_x;
    *p->y_pos = next_y;
}

void    move_left(t_map map, t_player *p)
{
    int next_x;
    int next_y;

    next_x = (int)(*p->x_pos + (p->direction.x * SPEED));
    next_y = (int)(*p->y_pos - (p->direction.y * SPEED));
    // tmp protection for the map size
    if (next_x >= map.max_width * CUBE_SIZE || next_y >= map.max_height * CUBE_SIZE)
        fatal("over the map");
    printf("next_x: %d, next_y: %d)\n", next_x, next_y);
    if (map.map[next_x / CUBE_SIZE][next_y / CUBE_SIZE] == '1')
        return ;
    *p->x_pos = next_x;
    *p->y_pos = next_y;
}

void    move_right(t_map map, t_player *p)
{
    int next_x;
    int next_y;

    next_x = (int)(*p->x_pos - (p->direction.x * SPEED));
    next_y = (int)(*p->y_pos + (p->direction.y * SPEED));
    // tmp protection for the map size
    if (next_x >= map.max_width * CUBE_SIZE || next_y >= map.max_height * CUBE_SIZE)
        fatal("over the map");
    printf("next_x: %d, next_y: %d)\n", next_x, next_y);
    if (map.map[next_x / CUBE_SIZE][next_y / CUBE_SIZE] == '1')
        return ;
    *p->x_pos = next_x;
    *p->y_pos = next_y;
}