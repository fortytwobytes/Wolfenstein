#include "../../includes/srcs.h"

bool	can_move(char block)
{
	const char *allowed_blocks;

	allowed_blocks = "0NSWEP";
	for (int i = 0; allowed_blocks[i]; i++) {
		if (block == allowed_blocks[i]) {
			return (true);
		}
	}
	return (false);
}

void    move_hook(void *param)
{
	t_var *var;

	var = param;

	var->old_time = var->c_time;
	var->c_time = (double) clock();
	double frame_time = (var->c_time - var->old_time) / 500000;
	//speed modifiers
	double move_speed = frame_time * 5.0; //the constant value is in squares/second
	double rot_speed = frame_time * 3.0; //the constant value is in radians/second

	if (mlx_is_key_down(var->mlx, MLX_KEY_ESCAPE)) {
		// end game
		end_game(var);
	}
	if (mlx_is_key_down(var->mlx, MLX_KEY_W)) {
		if (can_move(var->map.map[(int) (var->pos.x + var->dir.x * move_speed)][(int) (var->pos.y)]))
			var->pos.x += var->dir.x * move_speed;
		if (can_move(var->map.map[(int) (var->pos.x)][(int) (var->pos.y + var->dir.y * move_speed)]))
			var->pos.y += var->dir.y * move_speed;
	}
	if (mlx_is_key_down(var->mlx, MLX_KEY_S)) {
		if (can_move(var->map.map[(int) (var->pos.x - var->dir.x * move_speed)][(int) (var->pos.y)]))
			var->pos.x -= var->dir.x * move_speed;
		if (can_move(var->map.map[(int) (var->pos.x)][(int) (var->pos.y - var->dir.y * move_speed)]))
			var->pos.y -= var->dir.y * move_speed;
	}
	if (mlx_is_key_down(var->mlx, MLX_KEY_A)) {
		double new_x = var->pos.x - var->plane.x * move_speed;
		double new_y = var->pos.y - var->plane.y * move_speed;
		if (can_move(var->map.map[(int) new_x][(int) var->pos.y]))
		{
			var->pos.x = new_x;
		}
		if (can_move(var->map.map[(int) var->pos.x][(int) new_y]))
		{
			var->pos.y = new_y;
		}
	}
	if (mlx_is_key_down(var->mlx, MLX_KEY_D)) {
		double new_x = var->pos.x + var->plane.x * move_speed;
		double new_y = var->pos.y + var->plane.y * move_speed;
		if (can_move(var->map.map[(int) new_x][(int) var->pos.y]))
		{
			var->pos.x = new_x;
		}
		if (can_move(var->map.map[(int) var->pos.x][(int) new_y]))
		{
			var->pos.y = new_y;
		}
	}
	if (mlx_is_key_down(var->mlx, MLX_KEY_LEFT)) {
		//both camera direction and camera plane must be rotated
		double old_dir_x = var->dir.x;
		var->dir.x = var->dir.x * cos(rot_speed) - var->dir.y * sin(rot_speed);
		var->dir.y = old_dir_x * sin(rot_speed) + var->dir.y * cos(rot_speed);
		double old_plane_x = var->plane.x;
		var->plane.x = var->plane.x * cos(rot_speed) - var->plane.y * sin(rot_speed);
		var->plane.y = old_plane_x * sin(rot_speed) + var->plane.y * cos(rot_speed);
	}
	if (mlx_is_key_down(var->mlx, MLX_KEY_RIGHT)) {
		double old_dir_x = var->dir.x;
		var->dir.x = var->dir.x * cos(-rot_speed) - var->dir.y * sin(-rot_speed);
		var->dir.y = old_dir_x * sin(-rot_speed) + var->dir.y * cos(-rot_speed);
		double old_plane_x = var->plane.x;
		var->plane.x = var->plane.x * cos(-rot_speed) - var->plane.y * sin(-rot_speed);
		var->plane.y = old_plane_x * sin(-rot_speed) + var->plane.y * cos(-rot_speed);
	}
}

void draw_hook(void *args) {
	t_var *var;
	t_ray ray;
	int hit;
	int side;
	int x;

	var = args;
	memset(var->image->pixels, 0, var->image->width * var->image->height * sizeof(uint32_t));
	draw_floor_ceil(var->image);

	x = -1;
	while (++x < SCREEN_WIDTH) {
		//calculate ray position and direction
		ray.camera_x = 2 * x / (double) SCREEN_WIDTH - 1; //x-coordinate in camera space
		ray.ray_dir_x = var->dir.x + var->plane.x * ray.camera_x;
		ray.ray_dir_y = var->dir.y + var->plane.y * ray.camera_x;
		//which box of the map we're in
		ray.map_x = (int) var->pos.x;
		ray.map_y = (int) var->pos.y;

		//length of ray from one x or y-side to next x or y-side
		ray.delta_dist_x = (ray.ray_dir_x == 0) ? 1e00 : fabs(1 / ray.ray_dir_x);
		ray.delta_dist_y = (ray.ray_dir_y == 0) ? 1e00 : fabs(1 / ray.ray_dir_y);

		if (ray.ray_dir_x < 0) {
			ray.step_x = -1;
			ray.side_dist_x = (var->pos.x - ray.map_x) * ray.delta_dist_x;
		} else {
			ray.step_x = 1;
			ray.side_dist_x = (ray.map_x + 1.0 - var->pos.x) * ray.delta_dist_x;
		}
		if (ray.ray_dir_y < 0) {
			ray.step_y = -1;
			ray.side_dist_y = (var->pos.y - ray.map_y) * ray.delta_dist_y;
		} else {
			ray.step_y = 1;
			ray.side_dist_y = (ray.map_y + 1.0 - var->pos.y) * ray.delta_dist_y;
		}
		hit = 0; //was there a wall hit?
		while (hit == 0) {
			//jump to next map square, either in x-direction, or in y-direction
			if (ray.side_dist_x < ray.side_dist_y) {
				ray.side_dist_x += ray.delta_dist_x;
				ray.map_x += ray.step_x;
				side = 0;
			} else {
				ray.side_dist_y += ray.delta_dist_y;
				ray.map_y += ray.step_y;
				side = 1;
			}
			//Check if ray has hit a wall
			if (var->map.map[ray.map_x][ray.map_y] > '0') hit = 1;
		}
		ray.perp_wall_dist = (ray.side_dist_y - ray.delta_dist_y);
		if (side == 0)
			ray.perp_wall_dist = (ray.side_dist_x - ray.delta_dist_x);
		ray.line.line_height = (int) (SCREEN_HEIGHT / ray.perp_wall_dist);

		//calculate lowest and highest pixel to fill in current stripe
		ray.line.draw_start = -ray.line.line_height / 2 + SCREEN_HEIGHT / 2;
		if (ray.line.draw_start < 0)
			ray.line.draw_start = 0;
		ray.line.draw_end = ray.line.line_height / 2 + SCREEN_HEIGHT / 2;
		if (ray.line.draw_end >= SCREEN_HEIGHT)
			ray.line.draw_end = SCREEN_HEIGHT - 1;
		draw_vert_line(var->image, x, ray.line.draw_start, ray.line.draw_end);
	}
	t_vect_i p = get_player_xy_position(var->map.map);
	var->map.map[p.x][p.y] = '0';
	var->map.map[(int) var->pos.x][(int) var->pos.y] = 'P';

	char **minimap = get_minimap(var->map.map);
	draw_mini_map(var, minimap);
	free_split(minimap);
}
