#include "bsq.h"

int main(int argc, char **argv)
{
    FILE *file;
    t_map map;

    if (argc < 2)
        return 1;

    file = fopen(argv[1], "r");
    if (!file)
        return 1;

    if (!parse_header(file, &map))
    {
        fprintf(stderr, "map error\n");
        return 1;
    }

    if (!read_map(file, &map))
    {
        fprintf(stderr, "map error\n");
        return 1;
    }

    if (!validate_map(&map))
    {
        fprintf(stderr, "map error\n");
        return 1;
    }

    printf("map is valid!\n");

    free_map(&map);
    fclose(file);
    return 0;
}
