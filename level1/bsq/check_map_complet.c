#include "bsq.h"

/**
 * validate_map - 验证地图数据的合法性
 * @map: 指向地图结构体的指针
 * * 校验规则包括：
 * 1. 地图行数必须大于 0 且数据不为空。
 * 2. 地图必须是矩形（每一行的长度必须与第一行相等）。
 * 3. 每一行中的字符必须只能是 Header 定义的 empty 或 obstacle。
 * 4. 实际读取到的行数必须严格等于 Header 中声明的行数。
 * * 返回值: 1 (合法), 0 (非法，应触发 map error)
 */
static size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

int validate_map(t_map *map)
{
    int i;
    int j;         // 循环变量，定义在开头以符合 42 Norme 规范
    size_t first_len; // 存储地图第一行的宽度，作为后续各行宽度的基准

    // --- 基础安全性检查 ---
    // 如果 map 指针为空、网格未分配内存、声明行数 <= 0 或第一行不存在，直接判定非法
    if (!map || !map->grid || map->rows <= 0 || !map->grid[0])
        return (0);

    // 获取第一行的长度，后续所有行都必须与此长度对齐
    first_len = ft_strlen(map->grid[0]);
    i = 0;

    // --- 逐行校验逻辑 ---
    // 遍历每一行，直到达到声明的行数 rows 或遇到空行
    while (i < map->rows && map->grid[i])
    {
        // 1. 矩形校验 (等宽检查)
        // 使用 ft_strlen 计算当前行长度。如果与第一行长度不等，则地图不是矩形
        if (ft_strlen(map->grid[i]) != first_len)
            return (0);

        j = 0;
        // 2. 字符合法性校验
        // 遍历当前行的每一个字符
        while (j < first_len)
        {
            char c = map->grid[i][j];
            
            // 题目要求：地图中只能包含 'empty' 字符或 'obstacle' 字符
            // 如果出现了第三种字符（哪怕是 'full' 字符或不可见字符），均为非法
            if (c != map->empty && c != map->obstacle)
                return (0);
            j++;
        }
        i++; // 移动到下一行
    }

    // --- 行数完整性检查 ---
    // 3. 检查实际遍历到的有效行数 i 是否等于 Header 声明的 map->rows
    // 这一步能揪出“声明 10 行但文件只有 5 行”或者“文件行数多于声明”的错误
    if (i != map->rows)
        return (0);

    // 校验全部通过，将确认后的宽度记录到结构体中，方便后续解题算法使用
    map->cols = first_len;
    return (1);
}