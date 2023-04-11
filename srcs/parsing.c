#include "srcs.h"
#include <stdbool.h>

bool	is_texture_valid(void *mlx, char *path);
bool	is_filename_valid(char *filename);

bool	is_filename_valid(char *filename)
{
	int		extension_len;
	int		filename_len;
	char	*extension;

	extension = ".cub";
	filename_len = strlen(filename);
	extension_len = strlen(extension);
	if (filename_len <= extension_len)
		return (false);
	filename += filename_len - extension_len;
	if (strcmp(filename, extension))
		return (false);
	return (true);
}

bool	is_texture_valid(void *mlx, char *path)
{
	int		img_height;
	int		img_width;
	void	*img;

	img = mlx_xpm_file_to_image(mlx, path, &img_width, &img_height);
	if (img == NULL) {
		return (false);
	}
	free(img);
	return (true);
}

