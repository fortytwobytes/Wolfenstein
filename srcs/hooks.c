#include "../includes/srcs.h"

// TODO: fill the movements
// TODO: add mouse hook to change the player view
void	hooks(void *param) {
    t_var *var = param;

    if (mlx_is_key_down(var->mlx, MLX_KEY_ESCAPE) == true) {
        mlx_close_window(var->mlx);
    }
    if (mlx_is_key_down(var->mlx, MLX_KEY_A) == true) {
        var->img->instances[0].x -= 5;
    }
    if (mlx_is_key_down(var->mlx, MLX_KEY_D) == true) {
        var->img->instances[0].x += 5;
    }
    if (mlx_is_key_down(var->mlx, MLX_KEY_W) == true) {
        var->img->instances[0].y -= 5;
    }
    if (mlx_is_key_down(var->mlx, MLX_KEY_S) == true) {
        var->img->instances[0].y += 5;
    }
    if (mlx_is_key_down(var->mlx, MLX_KEY_LEFT) == true) {
    }
    if (mlx_is_key_down(var->mlx, MLX_KEY_RIGHT) == true) {
    }
}