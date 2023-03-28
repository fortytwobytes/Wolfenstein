#include "../srcs/srcs.h"

int main()
{
    assert(is_filename_valid(" .cub") == true);
    assert(is_filename_valid("map.cub") == true);
    assert(is_filename_valid("map .cub") == true);

    assert(is_filename_valid("") == false);
    assert(is_filename_valid("map") == false);
    assert(is_filename_valid("cub") == false);
    assert(is_filename_valid(".cub") == false);
    assert(is_filename_valid("map.CUB") == false);
    assert(is_filename_valid("map.txt") == false);
    assert(is_filename_valid("MAP.cUb") == false);
    assert(is_filename_valid("map.cub2") == false);
    assert(is_filename_valid("map. cub") == false);
    return 0;
}

