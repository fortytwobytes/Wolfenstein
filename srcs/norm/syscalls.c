#include "../../includes/srcs.h"

int ft_open(const char *pathname)
{
    int fd;

    fd = open(pathname, O_RDONLY);
    if (fd == -1)
        fatal(strerror(errno));
    return (fd);
}
