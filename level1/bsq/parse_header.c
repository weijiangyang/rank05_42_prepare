#include "bsq.h"

int parse_header(FILE *file, t_map *map)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t r;

	r = getline(&line, &len, file);
	if (r <= 0)
		return 0;

	map->rows = atoi(line);

	int i = 0;

	while (line[i] >= '0' && line[i] <= '9')
		i++;

	while (line[i] == ' ')
		i++;

	map->empty = line[i++];

	while (line[i] == ' ')
		i++;

	map->obstacle = line[i++];

	while (line[i] == ' ')
		i++;

	map->full = line[i];
	free(line);

	if (map->rows <= 0)
		return 0;

	if (map->empty == map->obstacle ||
		map->empty == map->full ||
		map->obstacle == map->full)
		return 0;

	if (map->empty < 32 || map->empty > 126)
		return 0;
	if (map->obstacle < 32 || map->obstacle > 126)
		return 0;
	if (map->full < 32 || map->full > 126)
		return 0;
	return 1;
}