#include "bsq.h"

int read_map(FILE *file, t_map* map)
{
    char* line = NULL;
    size_t len = 0;

    map->grid = malloc((map->rows + 1) * sizeof(char *));
    if (!map->grid)
        return 0;

    for (int i = 0; i < map->rows; i++)
    {
        if (getline(&line, &len, file) == -1)
            return 0;

        line[strcspn(line, "\r\n")] = '\0';

        map->grid[i] = strdup(line);
        if (!map->grid[i])
            return 0;
		
    }
	map->grid[map->rows] = NULL;
    free(line);
	return 1;
}