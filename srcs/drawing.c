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
            if (line[j] == '0')
                draw_square(var->minimap, x, y, BLACK);
            j++;
        }
        i++;
    }
}
