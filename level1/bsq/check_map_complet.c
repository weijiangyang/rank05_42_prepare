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
    int first_len;

    // 1. 基础检查
    if (!map || !map->grid || !map->grid[0])
        return (0);

    // 2. 获取基准宽度
    first_len = ft_strlen(map->grid[0]);
    if (first_len <= 0)
        return (0);

    i = 0;
    while (map->grid[i])
    {
        // 3. 长度检查
        if (ft_strlen(map->grid[i]) != first_len)
            return (0);

        // 4. 字符合法性检查 (这里直接原地检查，省去 check_line_valid 函数)
        for (int j = 0; j < first_len; j++)
        {
            char c = map->grid[i][j];
            if (c != map->empty && c != map->obstacle)
                return (0); // 发现非法字符（比如出现了 full 字符或其它杂质）
        }
        i++;
    }

    // 5. 行数匹配检查
    if (i != map->rows)
        return (0);

    map->cols = first_len;
    return (1);
}