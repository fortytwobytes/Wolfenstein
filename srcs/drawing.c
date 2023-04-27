#include "../includes/srcs.h"

static void draw_square(mlx_image_t *img, int x, int y, u_int32_t color)
{
    int x_end = x + CUBE_SIZE - 1;
    int y_end = y + CUBE_SIZE - 1;
    for (int xo = x; xo < x_end; xo++) {
        for (int yo = y; yo < y_end; yo++) {
            mlx_put_pixel(img, xo, yo, color);
        }
    }
}

void draw_player(void *params)
{
    mlx_image_t *player_img = params;
    for (uint x = 0; x < player_img->width; ++x) {
        for (uint y = 0; y < player_img->height; ++y) {
            mlx_put_pixel(player_img, x, y, RED);
        }
    }
}

void draw_map(void *params) {
    t_var *var = params;

    int i = 0;
    for (int x = 0; var->map.map[i]; x += CUBE_SIZE) {
        int j = 0;
        char *line = var->map.map[i];
        for (int y = 0; line[j]; y += CUBE_SIZE) {
            if (line[j] == '1')
                draw_square(var->minimap, x, y, WHITE);
            else
                draw_square(var->minimap, x, y, BLACK);
            j++;
        }
        i++;
    }
}

void    draw_direction(void *params)
{
    t_var *var = params;
    memset(var->rays->pixels, 0, var->rays->height * var->rays->width * sizeof(int32_t));
    int32_t x = *var->player.x_pos + (PLAYER_SIZE / 2);
    int32_t y = *var->player.y_pos + (PLAYER_SIZE / 2);
    int32_t x1 = x + var->player.direction.x;
    int32_t y1 = y + var->player.direction.y;

    printf("(x1: %d, y1: %d), angle %f\n", x1, y1, var->player.angle);
    draw_line(var->rays, (t_vect) {x,y}, (t_vect) {329,195}, GREEN);
}
