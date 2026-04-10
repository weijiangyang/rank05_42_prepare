#include "bsq.h"

int check_line_valid(t_map* map, char* line)
{
    if (!line)
        return 0;

    for (int i = 0; line[i]; i++)
    {
        if (line[i] != map->empty && line[i] != map->obstacle)
            return 0;
    }
    return 1;
}