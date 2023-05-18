/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouakch <onouakch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 17:09:19 by onouakch          #+#    #+#             */
/*   Updated: 2023/05/18 14:07:16 by onouakch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
# include <math.h>
#include <time.h>
#include "MLX42/include/MLX42/MLX42.h"

#define mapWidth 24
#define mapHeight 24
#define screenWidth 1024
#define screenHeight 512
#define texWidth 64
#define texHeight 64

// #define screenWidth 640
// #define screenHeight 480
// #define texWidth 64
// #define texHeight 64
// #define mapWidth 24
// #define mapHeight 24
typedef struct s_data
{
  mlx_t* mlx;
  mlx_image_t* image;
  double  pos_x;
  double  pos_y;
  double  dir_x;
  double  dir_y;
  double  plane_x;
  double  plane_y;
  double  c_time;
  double  old_time;
  mlx_image_t *img;

} t_data;

typedef struct s_line
{
  int line_height;
  int draw_start;
  int draw_end;
} t_line;

typedef struct s_ray
{
  double camera_x;
  double ray_dir_x;
  double ray_dir_y;
  double side_dist_x;
  double side_dist_y;
  double perp_wall_dist;
  double delta_dist_x;
  double delta_dist_y;
  int map_x;
  int map_y;
  int step_x;
  int step_y;
  t_line line;
} t_ray;

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

void    set_env(uint32_t buffer[screenHeight][screenWidth])
{
    int i;
    int j;

    uint32_t color = ft_pixel(0, 0, 0, 0 );
    i = -1;
    while (++i < screenWidth)
    {
      j = -1;
      while (++j < screenHeight && !buffer[j][i])
        buffer[j][i] = 0;
    }
    i = -1;
    while (++i < screenWidth)
    {
      j = screenHeight;
      while (--j >= 0 && !buffer[j][i])
        buffer[j][i] = ft_pixel(99,40,0,99);
    }
}

void    vert_line(mlx_image_t *image, int x, int drawStart, int drawEnd)
{
  uint32_t color = ft_pixel(104, 252, 0, 255);
    while (drawStart < drawEnd)
	        mlx_put_pixel(image, x , drawStart++, color);
}

int worldMap[mapWidth][mapHeight]=
{
  {4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4},
  {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,0,0,0,0,0,4},
  {4,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
  {4,0,4,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
  {4,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,0,0,0,0,0,4},
  {4,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,4,4,0,4,4,4,4,4},
  {4,0,4,0,0,0,0,4,0,4,0,4,0,4,0,4,4,0,0,0,4,4,4,4},
  {4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,4,4,0,0,0,0,0,0,4},
  {4,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,4,4,4},
  {4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,4,4,0,0,0,0,0,0,4},
  {4,0,0,0,0,0,0,4,0,0,0,0,0,0,0,4,4,0,0,0,4,4,4,4},
  {4,0,0,0,0,0,0,4,4,4,4,0,4,4,4,4,4,4,4,4,4,4,4,4},
  {4,4,4,4,4,4,4,4,4,4,4,0,4,4,4,4,4,4,4,4,4,4,4,4},
  {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
  {4,4,4,4,4,4,0,4,4,4,4,0,4,4,4,4,4,4,4,4,4,4,4,4},
  {4,4,4,4,4,4,0,4,4,4,4,0,4,4,4,4,4,4,4,4,4,4,4,4},
  {4,0,0,0,0,0,0,0,0,4,4,0,4,4,0,0,0,0,0,4,0,0,0,4},
  {4,0,0,0,0,0,0,0,0,0,0,0,4,4,0,0,4,0,0,4,0,0,0,4},
  {4,0,0,0,0,0,0,0,0,4,4,0,4,4,0,0,0,0,0,4,4,0,4,4},
  {4,0,4,0,4,0,0,0,0,4,4,0,0,0,0,0,4,0,0,0,0,0,0,4},
  {4,0,0,4,0,0,0,0,0,4,4,0,4,4,0,0,0,0,0,4,4,0,4,4},
  {4,0,4,0,4,0,0,0,0,4,4,0,4,4,0,0,4,0,0,4,0,0,0,4},
  {4,0,0,0,0,0,0,0,0,4,4,0,4,4,0,0,0,0,0,4,0,0,0,4},
  {4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4}
};

typedef struct vv
{
  int x, y;
}t_vect_i;


uint32_t	get_image_color(mlx_image_t *image, t_vect_i p)
{
	uint32_t	color;
	uint32_t	index;

	index = (p.y % image->height * image->width + p.x % image->width) * 4;
	color = image->pixels[index] << 24;
	color |= image->pixels[index + 1] << 16;
	color |= image->pixels[index + 2] << 8;
	color |= 0x000000FF;
	return (color);
}

// uint32_t texture[texWidth * texHeight];

uint32_t texture[texHeight * texWidth];

uint32_t buffer[screenHeight][screenWidth];

void  ft_draw(void *args)
{
  t_data *data;
  t_ray   ray;
  int hit;
  int side;
  int x;
  

  data = args;
  mlx_delete_image(data->mlx, data->image);
  data->image = mlx_new_image(data->mlx, screenWidth, screenHeight);
	mlx_image_to_window(data->mlx, data->image, 0, 0);
  // set_env(data->image);

  x = -1;
  while(++x < screenWidth)
  {
    //calculate ray position and direction
    ray.camera_x = 2 * x / (double)screenWidth - 1; //x-coordinate in camera space
    ray.ray_dir_x = data->dir_x + data->plane_x * ray.camera_x;
    ray.ray_dir_y = data->dir_y + data->plane_y * ray.camera_x;
          //which box of the map we're in
    ray.map_x = (int)data->pos_x;
    ray.map_y = (int)data->pos_y;

       //length of ray from one x or y-side to next x or y-side
      //  ray.delta_dist_x = (ray.ray_dir_x == 0) ? 1e00 : fabs(1 / ray.ray_dir_x);
      //  ray.delta_dist_y = (ray.ray_dir_y == 0) ? 1e00 : fabs(1 / ray.ray_dir_y);
       ray.delta_dist_x = (ray.ray_dir_x == 0) ? 1e00 : fabs(1 / ray.ray_dir_x);
       ray.delta_dist_y = (ray.ray_dir_y == 0) ? 1e00 : fabs(1 / ray.ray_dir_y);

      if (ray.ray_dir_x < 0)
      {
        ray.step_x = -1;
        ray.side_dist_x = (data->pos_x - ray.map_x) * ray.delta_dist_x;
      }
      else
      {
        ray.step_x = 1;
        ray.side_dist_x = (ray.map_x + 1.0 - data->pos_x) * ray.delta_dist_x;
      }
      if (ray.ray_dir_y < 0)
      {
        ray.step_y = -1;
        ray.side_dist_y = (data->pos_y - ray.map_y) * ray.delta_dist_y;
      }
      else
      {
        ray.step_y = 1;
        ray.side_dist_y = (ray.map_y + 1.0 - data->pos_y) * ray.delta_dist_y;
      }
      hit = 0; //was there a wall hit?
      while (hit == 0)
      {
        //jump to next map square, either in x-direction, or in y-direction
        if (ray.side_dist_x < ray.side_dist_y)
        {
          ray.side_dist_x += ray.delta_dist_x;
          ray.map_x += ray.step_x;
          side = 0;
        }
        else
        {
          ray.side_dist_y += ray.delta_dist_y;
          ray.map_y += ray.step_y;
          side = 1;
        }
        //Check if ray has hit a wall
        if (worldMap[ray.map_x][ray.map_y] > 0) hit = 1;
      }
      if(side == 0)
        ray.perp_wall_dist = (ray.side_dist_x - ray.delta_dist_x);
      else
        ray.perp_wall_dist = (ray.side_dist_y - ray.delta_dist_y);
      ray.line.line_height = (int)(screenHeight / ray.perp_wall_dist);

      // int pitch = 100;
      //calculate lowest and highest pixel to fill in current stripe
      ray.line.draw_start = -ray.line.line_height / 2 + screenHeight / 2 /*+ pitch*/;
      if(ray.line.draw_start < 0)
        ray.line.draw_start = 0;
      ray.line.draw_end = ray.line.line_height / 2 + screenHeight / 2 /*+ pitch*/;
      if(ray.line.draw_end >= screenHeight)
        ray.line.draw_end = screenHeight - 1;

      //texturing calculations
      // int texNum = worldMap[ray.map_x][ray.map_y] - 1; //1 subtracted from it so that texture 0 can be used!

      //calculate value of wallX
      double wallX; //where exactly the wall was hit
      if (side == 0) wallX = data->pos_y + ray.perp_wall_dist * ray.ray_dir_y;
      else           wallX = data->pos_x + ray.perp_wall_dist * ray.ray_dir_x;
      wallX -= floor((wallX));

      //x coordinate on the texture
      int texX = (int)(wallX * (double)(texWidth));
      if(side == 0 && ray.ray_dir_x > 0) texX = texWidth - texX - 1;
      if(side == 1 && ray.ray_dir_y < 0) texX = texWidth - texX - 1;
         // How much to increase the texture coordinate per screen pixel
      double step = 1.0 * texHeight / ray.line.line_height;
      // Starting texture coordinate
      double texPos = (ray.line.draw_start - screenHeight / 2 + ray.line.line_height / 2) * step;
      
      for(int y = ray.line.draw_start; y<ray.line.draw_end; y++)
      {
        // Cast the texture coordinate to integer, and mask with (32 - 1) in case of overflow
        int texY = (int)texPos & (texHeight - 1);
        texPos += step;
        // uint32_t color = texture[texHeight * texY + texX];
        //make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
        // if(side == 1) color = (color >> 1) & 8355711;
        buffer[y][x] = get_image_color(data->img, (t_vect_i) {texX, texY});
      }
  }
  set_env(buffer);
  int i = -1;
  int j;
  while (++i < screenWidth)
  {
    j = -1;
    while (++j < screenHeight)
      mlx_put_pixel(data->image, i , j, buffer[j][i]);
  }
  for(int y = 0; y < screenHeight; y++) for(int x = 0; x < screenWidth; x++) buffer[y][x] = 0;
}

void  ft_hook(void *args)
{
  t_data  *data;

  data = args;
  
   //clear the buffer instead of cls()
  // data->old_time = data->c_time;
  // data->c_time = clock();
  // double frameTime = (data->c_time - data->old_time) / 600000; 
  double frameTime = 0.03; 
  // printf("time %f\n", frameTime);
  // pause();
  //speed modifiers
  double moveSpeed = frameTime * 5.0; //the constant value is in squares/second
  double rotSpeed = frameTime * 3.0; //the constant value is in radians/second

	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
  {
    if(worldMap[(int)(data->pos_x + data->dir_x * moveSpeed)][(int)(data->pos_y)] == false)
       data->pos_x += data->dir_x * moveSpeed;
    if(worldMap[(int)(data->pos_x)][(int)(data->pos_y + data->dir_y * moveSpeed)] == false)
      data->pos_y += data->dir_y * moveSpeed;
  }
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
  {
    if(worldMap[(int)(data->pos_x - data->dir_x * moveSpeed)][(int)(data->pos_y)] == false)
      data->pos_x -= data->dir_x * moveSpeed;
    if(worldMap[(int)(data->pos_x)][(int)(data->pos_y - data->dir_y * moveSpeed)] == false)
      data->pos_y -= data->dir_y * moveSpeed;
  }
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
  {
    //both camera direction and camera plane must be rotated
      double oldDirX = data->dir_x;
      data->dir_x = data->dir_x * cos(rotSpeed) - data->dir_y * sin(rotSpeed);
      data->dir_y = oldDirX * sin(rotSpeed) + data->dir_y * cos(rotSpeed);
      double oldPlaneX = data->plane_x;
      data->plane_x = data->plane_x * cos(rotSpeed) - data->plane_y * sin(rotSpeed);
      data->plane_y = oldPlaneX * sin(rotSpeed) + data->plane_y * cos(rotSpeed);
  }
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
  {
    double oldDirX = data->dir_x;
    data->dir_x = data->dir_x * cos(-rotSpeed) - data->dir_y * sin(-rotSpeed);
    data->dir_y = oldDirX * sin(-rotSpeed) + data->dir_y * cos(-rotSpeed);
    double oldPlaneX = data->plane_x;
    data->plane_x = data->plane_x * cos(-rotSpeed) - data->plane_y * sin(-rotSpeed);
    data->plane_y = oldPlaneX * sin(-rotSpeed) + data->plane_y * cos(-rotSpeed);
  }
  if (mlx_is_key_down(data->mlx, MLX_KEY_A))
  {
    double	new_x;
	double	new_y;

	new_x = data->pos_x - data->plane_x * moveSpeed;
	new_y = data->pos_y - data->plane_y * moveSpeed;
  if(worldMap[(int)(new_x)][(int)(data->pos_y)] == false)
      data->pos_x = new_x;
    if(worldMap[(int)(data->pos_x)][(int)(new_y)] == false)
      data->pos_y = new_y;
  }
  if (mlx_is_key_down(data->mlx, MLX_KEY_D))
  {
    double	new_x;
	double	new_y;

	new_x = data->pos_x + data->plane_x * moveSpeed;
	new_y = data->pos_y + data->plane_y * moveSpeed;
  if(worldMap[(int)(new_x)][(int)(data->pos_y)] == false)
      data->pos_x = new_x;
    if(worldMap[(int)(data->pos_x)][(int)(new_y)] == false)
      data->pos_y = new_y;
  }
}


void  ft_init(t_data *data)
{
  data->pos_x = 5.5;
  data->pos_y = 5.5;
  /*
    -*- North cords -*-
    dir (-1, 0) / plane (0, 0.66)
    -*- South cords -*-
    dir(1, 0) / plane(0, -0.66)
    -*- East cords  -*-
    dir(0,1) / plane(0.66,0)
    -*- West cords  -*-
    dir(0,-1) / plane(-0.66, 0)
  */
  data->dir_x = -1;
  data->dir_y = 0;
  data->plane_x = 0;
  data->plane_y = 0.66;
  data->c_time = 0;
  data->old_time = 0;
  data->mlx = mlx_init(screenWidth, screenHeight, "MLX42", true);
}

// gcc main.c MLX42/build/libmlx42.a -Iinclude -lglfw -L"/Users/$USER/.brew/opt/glfw/lib/"

int32_t main(int32_t argc, const char* argv[])
{
  t_data  data;
        

  ft_init(&data);
  mlx_texture_t *te = mlx_load_png(argv[1]);
  data.img = mlx_texture_to_image(data.mlx, te);
  mlx_resize_image(data.img, texWidth, texHeight);
  mlx_delete_texture(te);
  xpm_t* text;
	
	// Convert texture to a displayable image
	// mlx_image_t* img = mlx_texture_to_image(data.mlx, &text->texture);
  // text = mlx_load_xpm42("./eagle.xpm42");
  // texture = malloc(texHeight * texWidth * sizeof(uint8_t));
  // texture = text->texture.pixels;
  
  for(int x = 0; x < texWidth; x++)
  {
  for(int y = 0; y < texHeight; y++)
  {
      // int rgb = text->texture.pixels[text->texture.width * y + x];
      // texture[texWidth * y + x] = xorcolor + 256 * xorcolor + 65536 * xorcolor; //xor greyscale
      texture[texWidth * y + x] = get_image_color(data.img, (t_vect_i) {x, y});
      // texture[text->texture.width * y + x] = (rgb * 65536) + (rgb * 256) + rgb;
      // printf("%d , ", text->texture.pixels[x]);
  }
  }
  // pause();
  
  mlx_loop_hook(data.mlx, ft_draw, &data);
  mlx_loop_hook(data.mlx, ft_hook, &data);

  mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	return (EXIT_SUCCESS);
}
