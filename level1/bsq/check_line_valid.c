#include "bsq.h"

/**
 * 检查单行地图字符是否合法
 * @param map: 包含合法字符定义的结构体 (empty, obstacle)
 * @param line: 当前需要检查的字符串行
 * @return: 如果整行字符均合法返回 1，否则返回 0
 */
int check_line_valid(t_map* map, char* line)
{
    // --- 1. 安全检查 ---
    // 如果传入的行指针为空，直接视为非法
    if (!line)
        return 0;

    // --- 2. 遍历字符串 ---
    // 循环直到遇到字符串结束符 '\0'
    for (int i = 0; line[i]; i++)
    {
        // --- 3. 字符比对 ---
        // 检查当前字符 line[i] 是否既不是“空位字符”，也不是“障碍物字符”
        // 注意：BSQ 地图原始内容中不应包含“填充字符”(full)，
        // 因为那是 solve_bsq 之后才会填进去的。
        if (line[i] != map->empty && line[i] != map->obstacle)
        {
            // 一旦发现任何不属于这两类的字符（包括空格、制表符等），立刻报错
            return 0;
        }
    }

    // --- 4. 校验通过 ---
    // 遍历完整行没有发现异常字符，返回 1
    return 1;
}