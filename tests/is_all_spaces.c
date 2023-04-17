#include "../includes/srcs.h"

int main() {
    char *line1 = "   ";
    assert(is_all_spaces(line1) == true);

    char *line2 = "  \t";
    assert(is_all_spaces(line2) == true);

    char *line3 = "  \t  ";
    assert(is_all_spaces(line3) == true);

    char *line4 = "                   NOT";
    assert(is_all_spaces(line4) == false);

    char *line5 = "  \t  NOT";
    assert(is_all_spaces(line5) == false);
}