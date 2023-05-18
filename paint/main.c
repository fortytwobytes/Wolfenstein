// -----------------------------------------------------------------------------
// Codam Coding College, Amsterdam @ 2022-2023 by W2Wizard.
// See README in the root project for more information.
// -----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
# include <math.h>
#include "MLX42/include/MLX42/MLX42.h"

#define WIDTH 512
#define HEIGHT 512

static mlx_image_t* image;

// -----------------------------------------------------------------------------

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

void ft_randomize(void* param)
{
	for (int32_t i = 0; i < image->width; ++i)
	{
		for (int32_t y = 0; y < image->height; ++y)
		{
			uint32_t color = ft_pixel(
				rand() % 0xFF, // R
				rand() % 0xFF, // G
				rand() % 0xFF, // B
				rand() % 0xFF  // A
			);
			mlx_put_pixel(image, i, y, color);
		}
	}
}

void ft_hook(void* param)
{
	mlx_t* mlx = param;

	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
		image->instances[0].y -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
		image->instances[0].y += 5;
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		image->instances[0].x -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		image->instances[0].x += 5;
}

// -----------------------------------------------------------------------------

int32_t main(int32_t argc, const char* argv[])
{
	mlx_t* mlx;

	// Gotta error check this stuff
	mlx = mlx_init(320, 200, "MLX42", true);
	image = mlx_new_image(mlx, 320, 200);
	mlx_image_to_window(mlx, image, 0, 0);

    //*****************************************
    int maap[5][5] = {
        {1,1,1,1,1},
        {1,0,0,0,0},
        {0,0,0,0,0},
        {0,0,0,0,0}
    };
    int w_width = 5 * 64;
    int w_height = 5 * 64;
    //  setting player position
    int ray_count = 320;
    
    double angle = 90.0;
    double angle_increment = 90.0 / 320.0;
    int pos_x = 1;
    int pos_y = 3;
    int direction_x = (64 * pos_x) + 32;
    int direction_y = (64 * pos_y) + 32;
    double rays_angle = angle / w_width;
    double  end_angle = angle - (angle / 2);
    int proj_plan_dist = (320 / 2) / tan((angle / 2) * M_PI / 180.0);
    while (--ray_count > 160)
    {
        int y = ((int)(direction_y / 64)) * 64 -1;
        int x = direction_x + (direction_y - y) / tan(angle * M_PI / 180.0);
        int xa = 64 / tan(angle * M_PI / 180.0);
        int ya = -64;
        while (maap[y / 64][x / 64] != 1)
        {
            printf("(%d,%d) = [%d]\n", x / 64, y / 64, maap[y / 64][x / 64]);
            x += xa;
            y += ya;
        }
        printf("(%d,%d) = [%d]\n------------\n", x / 64, y / 64, maap[y / 64][x / 64]);
        double horz_ray_dist = sqrt(pow(direction_x - x, 2) + pow(direction_y - y, 2)) /* cos(30.0 *( M_PI / 180.0))*/;
        horz_ray_dist *= cos((90 - angle) * M_PI / 180.0);
        // double horz_ray_dist = sqrt(pow(direction_x - x, 2) + pow(direction_y - y, 2));
        x = ((int)(direction_x / 64)) * 64 + 64;
        y = direction_y + (direction_x - x) * tan(angle * M_PI / 180.0);
        xa = 64;
        ya = 64 * tan(angle * M_PI / 180.0);
        while (maap[y / 64][x / 64] != 1)
        {
            printf("(%d,%d) = [%d]\n", x / 64, y / 64, maap[y / 64][x / 64]);
            x += xa;
            y -= ya;
        }
        printf("(%d,%d) = [%d]\n*************\n", x / 64, y / 64, maap[y / 64][x / 64]);
        // double vert_ray_dist = sqrt(pow(direction_x - x, 2) + pow(direction_y - y, 2)) * cos((30 + angle_increment) * M_PI / 180.0);
        // double vert_ray_dist = sqrt(pow(direction_x - x, 2) + pow(direction_y - y, 2));
        // double slice_height = (64.0 / vert_ray_dist) * proj_plan_dist; 
        double   slice_height = (64.0 / horz_ray_dist) * proj_plan_dist;
        // double   slice_height = 0.2310469314 * horz_ray_dist;
        printf("horz => %f | wall height: %f\n", sqrt(pow(direction_x - x, 2) + pow(direction_y - y, 2)), horz_ray_dist);
        // if (horz_ray_dist < vert_ray_dist)
        uint32_t color = ft_pixel(
			rand() % 0xFF, // R
			rand() % 0xFF, // G
			rand() % 0xFF, // B
			rand() % 0xFF  // A
		);
        int i = 100 - (floor(slice_height) / 2);
        int end = i + floor(slice_height);
        while (i <= end)
	        mlx_put_pixel(image, ray_count , i++, color);
        angle += angle_increment;
    }
    // distance from player to the projection plane
    //  Angle between subsequent rays
    //  starting angle
    //  horizontal intersection
    
    
    // printf("Horizontal wall cords (%d,%d) = [%d]\n", x / 64, y / 64, maap[y / 64][x / 64]);
    
    // printf("distance is = %f\n", horz_ray_dist);
    //  vertical intersection
    
    // printf("Vertical wall cords (%d,%d) = [%d]\n", x / 64, y / 64, maap[y / 64][x / 64]);
    
    // printf("distance is = %f\n", vert_ray_dist);
    // //  calculate the wall height
    
    // printf("the slice height = %d\n", (int)slice_height + 1);


    //*****************************************
   
	
    
    // int i = 
    // for (int32_t i = 0; i < image->width; ++i)
	// {
	// 	for (int32_t y = 0; y < image->height; ++y)
	// 	{
	// 		uint32_t color = ft_pixel(
	// 			rand() % 0xFF, // R
	// 			rand() % 0xFF, // G
	// 			rand() % 0xFF, // B
	// 			rand() % 0xFF  // A
	// 		);
	// 		mlx_put_pixel(image, i, y, color);
	// 	}
	// }
	// mlx_loop_hook(mlx, ft_randomize, mlx);
	// mlx_loop_hook(mlx, ft_hook, mlx);

	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
