#include "srcs.h"

void	move_player(t_var *var, int option)
{
	if (option == MLX_KEY_W)
	{
		var->player.position.y += var->player.direction.y;
        var->player.position.x += var->player.direction.x;
	}
	if (option == MLX_KEY_DOWN)
	{
        var->player.position.y -= var->player.direction.y;
        var->player.position.x -= var->player.direction.x;

	}
	if (option == MLX_KEY_RIGHT)
	{
        // TODO: add later
	}
	if (option == MLX_KEY_LEFT)
	{
        // TODO: add later
	}
}

void	change_direction(t_var *var, int option)
{
	if (option == MLX_KEY_LEFT)
	{
		var->player.angle -= ROTATE_SPEED;
        if (var->player.angle < 0)
        {
            var->player.angle += 2 * PI;
        }
        var->player.direction.x = cos(var->player.angle) * 5;
        var->player.direction.y = sin(var->player.angle) * 5;
	}
	if (option == MLX_KEY_RIGHT)
	{
		var->player.angle += ROTATE_SPEED;
        if (var->player.angle > 2 * PI)
        {
            var->player.angle -= 2 * PI;
        }
        var->player.direction.x = cos(var->player.angle) * 5;
        var->player.direction.y = sin(var->player.angle) * 5;
	}
}

void	hooks(mlx_key_data_t keydata, void *param)
{
	t_var	*var;

	var = (t_var *)param;
	if (keydata.key == MLX_KEY_W)
		move_player(var, MLX_KEY_W);
	if (keydata.key == MLX_KEY_S)
		move_player(var, MLX_KEY_S);
	if (keydata.key == MLX_KEY_A)
		move_player(var, MLX_KEY_A);
	if (keydata.key == MLX_KEY_D)
		move_player(var, MLX_KEY_D);
	if (keydata.key == MLX_KEY_LEFT)
		change_direction(var, MLX_KEY_LEFT);
	if (keydata.key == MLX_KEY_RIGHT)
		change_direction(var, MLX_KEY_RIGHT);
}
