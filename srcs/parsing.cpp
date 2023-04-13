#include "srcs.h"

void	is_texture_valid(void *mlx, char *path);
bool	is_filename_valid(char *filename);

void	is_texture_valid(void *mlx, char *path)
{
	int		img_height;
	int		img_width;
	void	*img;

	img = mlx_xpm_file_to_image(mlx, path, &img_width, &img_height);
	if (img == NULL)
		fatal("invalid texture");
	free(img);
}

bool	is_filename_valid(char *filename)
{
	int		extension_len;
	int		filename_len;
	char	*extension;

	extension = ".cub";
	filename_len = ft_strlen(filename);
	extension_len = ft_strlen(extension);
	if (filename_len <= extension_len)
		return (false);
	filename += filename_len - extension_len;
	if (strcmp(filename, extension))
		return (false);
	return (true);
}

bool	is_all_num(char **elements)
{
	int	i;
	int	j;

	i = -1;
	while (elements[++i])
	{
		j = -1;
		while (elements[i][++j])
		{
			if (elements[i][j] < '0' || elements[i][j] > '9')
				return (false);
		}
	}
	return (true);
}

bool	is_space(char c)
{
	if ((c >= '\t' && c <= '\r') || c == ' ')
		return (true);
	return (false);
}

void	parse_cub_file(t_var *var, char *path)
{
	int	fd;

	var->map->map = ft_calloc(sizeof(t_map));
	fd = open(path, O_RDONLY);
	if (fd == -1)
		fatal("can't open the map file");
	parse_elements(fd, var->map);
	close(fd);
	fd = open(path, O_RDONLY);
	parse_map(fd, var->map);
	puts("in");
	close(fd);
}
