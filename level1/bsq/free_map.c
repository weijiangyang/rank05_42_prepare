#include "bsq.h"

void free_map(t_map *map)
{
    int i;

    // 1. 安全检查：如果 map 指针本身为空，或者 grid 还没分配，直接返回
    if (!map || !map->grid)
        return;

    // 2. 逐行释放
    i = 0;
    while (i < map->rows)
    {
        // 只有当这一行确实分配了内存时才释放
        if (map->grid[i])
        {
            free(map->grid[i]);
            map->grid[i] = NULL; // 养成良好的置空习惯
        }
        i++;
    }

    // 3. 释放行指针数组本身
    free(map->grid);
    map->grid = NULL; // 防止野指针
}