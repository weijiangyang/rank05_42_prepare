#include "bsq.h"

// 如果不准用 strlen，手写一个简单的
int ft_strlen(char *str)
{
    int i = 0;
    while (str && str[i])
        i++;
    return (i);
}

int validate_map(t_map *map)
{
    int i;
    int j; // 变量定义在开头，符合 Norme
    int first_len;

    if (!map || !map->grid || map->rows <= 0 || !map->grid[0])
        return (0);

    first_len = ft_strlen(map->grid[0]);
    i = 0;
    while (i < map->rows && map->grid[i])
    {
        // 1. 检查长度是否与第一行一致
        if (ft_strlen(map->grid[i]) != (size_t)first_len)
            return (0);

        j = 0;
        while (j < first_len)
        {
            char c = map->grid[i][j];
            // 2. 严格校验字符：只能是空位或障碍
            if (c != map->empty && c != map->obstacle)
                return (0);
            j++;
        }
        i++;
    }
    // 3. 检查读取的总行数是否严格等于 Header 声明的 rows
    if (i != map->rows)
        return (0);

    map->cols = first_len;
    return (1);
}