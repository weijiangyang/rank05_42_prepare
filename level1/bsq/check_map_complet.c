#include "bsq.h"
int validate_map(t_map *map)
{
	int len;
	int cur_len;
	int i;
	
	if (!map || !map->grid || !map->grid[0])
		return 0;

	len = strlen(map->grid[0]);
	if (len <= 0)
		return 0;

	i = 0;
	while (map->grid[i])
	{
		cur_len = strlen(map->grid[i]);
		if (cur_len != len)
			return 0;
		if (!check_line_valid(map, map->grid[i]))
			return 0;
		i++;
	}

	if (i != map->rows)
		return 0;

	map->cols = len;

	return 1;
}