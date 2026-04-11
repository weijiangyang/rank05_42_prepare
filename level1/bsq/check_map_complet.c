#include "bsq.h"

/**
 * 验证地图的合法性
 * 检查项：
 * 1. 指针是否有效
 * 2. 地图是否为空
 * 3. 每一行的长度是否严格相等（必须是矩形）
 * 4. 每一行是否只包含允许的字符 (empty, obstacle)
 * 5. 实际读取到的行数是否等于 Header 中声明的 rows
 */
int validate_map(t_map *map)
{
    int len;      // 第一行的长度（基准长度）
    int cur_len;  // 当前行的长度
    int i;        // 行计数器
    
    // --- 1. 基础安全检查 ---
    // 确保 map 结构体、网格指针以及第一行数据都存在
    if (!map || !map->grid || !map->grid[0])
        return 0;

    // --- 2. 获取基准宽度 ---
    // 以第一行的长度作为标准，后续所有行都必须与此相等
    len = strlen(map->grid[0]);
    if (len <= 0)
        return 0; // 地图宽度不能为 0

    i = 0;
    // --- 3. 逐行校验 ---
    // 遍历 grid 数组，直到遇到 read_map 末尾设置的 NULL
    while (map->grid[i])
    {
        cur_len = strlen(map->grid[i]);
        
        // 校验：当前行长度是否与第一行一致
        if (cur_len != len)
            return 0;
            
        // 校验：调用辅助函数，检查该行是否包含非法字符
        //（通常 check_line_valid 会检查字符是否只属于 map->empty 或 map->obstacle）
        if (!check_line_valid(map, map->grid[i]))
            return 0;
            
        i++; // 行数累加
    }

    // --- 4. 行数一致性检查 ---
    // 实际读取到的行数 (i) 必须等于 Header 解析出来的 map->rows
    if (i != map->rows)
        return 0;

    // --- 5. 赋值列数 ---
    // 验证全部通过后，记录地图的列数，供后续 solve_bsq 使用
    map->cols = len;

    return 1; // 地图合法
}