#include "libc/libc.h"
#include "srcs/srcs.h"
#include <sys/fcntl.h>

// float px, py;
// 
// 
// int map[8][8] = {
// 	{1, 1, 1, 1, 1, 1, 1, 1},
// 	{1, 0, 0, 0, 0, 0, 1, 1},
// 	{1, 0, 0, 1, 1, 0, 0, 1},
// 	{1, 0, 0, 0, 1, 1, 0, 1},
// 	{1, 1, 1, 0, 1, 0, 0, 1},
// 	{1, 0, 0, 0, 1, 0, 1, 1},
// 	{1, 0, 1, 0, 0, 0, 0, 1},
// 	{1, 1, 1, 1, 1, 1, 1, 1}
// };
// 
// void draw_tile(void *mlx, void *win, int x, int y, int color, int size) {
//     int x_end = x + size - 1;
//     int y_end = y + size - 1;
//     for (int i = x; i < x_end; i++) {
//         for (int j = y; j < y_end; j++) {
//             mlx_pixel_put(mlx, win, i, j, color);
//         }
//     }
// }
// 
// int	move(int keycode, void *p) {
// 
// 	(ss*)p;
// 
// 	if (keycode == UP) {
// 		px -= 5;
// 	}
// 	if (keycode == DOWN) {
// 		px += 5;
// 	}
// 	if (keycode == LEFT) {
// 		py -= 5;
// 	}
// 	if (keycode == RIGHT) {
// 		py -= 5;
// 	}
// 	draw_tile(p->mlx, p->win, px, py, 0x00FFF000, 32);
// 	return 0;
// }
// 
// int main() {
// 
// 	typedef struct ss {
// 		void *mlx;
// 		void *win;
// 	}ss;
// 
// 	ss *s;
// 
// 	void *mlx = mlx_init();
// 	void *win = mlx_new_window(mlx, 1024, 512, "Cube 3D");
// 
// 	s->mlx = mlx;
// 	s->win = win;
// 
// 	int x_start = 0, y_start = 0;
// 	for (int i = 0; i < 8; i++) {
// 		int x = x_start;
// 		for (int j = 0; j < 8; j++) {
// 			if (map[i][j] == 1) {
// 				draw_tile(mlx, win, x, y_start, 0x00808080, CUBE_SIZE);
// 			}
// 			else {
// 				draw_tile(mlx, win, x, y_start, 0x00FFFFFF, CUBE_SIZE);
// 			}
// 			x += CUBE_SIZE;
// 		}
// 		y_start += CUBE_SIZE;
// 	}
// 	px = 128; py = 128;
// 	
// 	draw_tile(mlx, win, px, py, 0x00FFF000, 32);
// 
// 	mlx_key_hook(win, move, s);
// 
// 	mlx_loop(mlx);
// }
// 
//

int main(int ac, char *av[]) {

	void *mlx = mlx_init();

	bool ret = is_texture_valid(mlx, av[1]);
	printf("%d\n", ret);

int main(int argc, char *argv[])
{
	// printf("hello world\n");
	parse_map(argv[1]);
	return (0);

}

