#include "srcs.h"

void	move_player(t_var *var, int option)
{
	if (option == UP)
	{
		var->player.position.y += var->player.direction.y;
        var->player.position.x += var->player.direction.x;
	}
	if (option == DOWN)
	{
        var->player.position.y -= var->player.direction.y;
        var->player.position.x -= var->player.direction.x;

	}
	if (option == RIGHT)
	{
        // TODO: add later
	}
	if (option == LEFT)
	{
        // TODO: add later
	}
}

void	change_direction(t_var *var, int option)
{
	if (option == LEFT_ARROW)
	{
		var->player.angle -= ROTATE_SPEED;
        if (var->player.angle < 0)
        {
            var->player.angle += 2 * PI;
        }
        var->player.direction.x = cos(var->player.angle) * 5;
        var->player.direction.y = sin(var->player.angle) * 5;
	}
	if (option == RIGHT_ARROW)
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

int	hooks(int keycode, void *ptr)
{
	t_var	*var;

	var = (t_var *)ptr;
	if (keycode == UP)
		move_player(var, UP);
	else if (keycode == DOWN)
		move_player(var, DOWN);
	else if (keycode == LEFT)
		move_player(var, LEFT);
	else if (keycode == RIGHT)
		move_player(var, RIGHT);
	else if (keycode == LEFT_ARROW)
		change_direction(var, LEFT_ARROW);
	else if (keycode == RIGHT_ARROW)
		change_direction(var, RIGHT_ARROW);
	return (1);
}
