#include "srcs.h"

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

