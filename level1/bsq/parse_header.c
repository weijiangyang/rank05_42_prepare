#include "bsq.h"

/**
 * 解析地图文件的第一行配置信息
 * 预期格式示例: "9.ox" (9行, .为空位, o为障碍, x为填充)
 * 或者带空格的格式: "9 . o x"
 */
int parse_header(FILE *file, t_map *map)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t r;

    // --- 1. 读取文件的第一行 ---
    r = getline(&line, &len, file);
    if (r <= 0)
        return 0; // 读取失败或文件为空

    // --- 2. 提取地图行数 ---
    // atoi 会转换开头的数字部分，直到遇到非数字字符
    map->rows = atoi(line);

    int i = 0;
    // 跳过已经解析过的数字部分
    while (line[i] >= '0' && line[i] <= '9')
        i++;

    // --- 3. 提取三个核心字符 ---
    
    // 跳过数字后的空格，提取 'empty' (空位字符)
    while (line[i] == ' ')
        i++;
    map->empty = line[i++];

    // 跳过空格，提取 'obstacle' (障碍物字符)
    while (line[i] == ' ')
        i++;
    map->obstacle = line[i++];

    // 跳过空格，提取 'full' (填充字符)
    while (line[i] == ' ')
        i++;
    map->full = line[i];

    // 释放由 getline 自动分配的临时内存
    free(line);

    // --- 4. 合法性检查 (Validation) ---

    // 检查行数是否有效
    if (map->rows <= 0)
        return 0;

    // 检查三个字符是否各不相同（不能重复使用同一个字符）
    if (map->empty == map->obstacle ||
        map->empty == map->full ||
        map->obstacle == map->full)
        return 0;

    // 检查字符是否为可打印字符 (ASCII 32-126)
    // 32 是空格, 126 是 '~'
    if (map->empty < 32 || map->empty > 126)
        return 0;
    if (map->obstacle < 32 || map->obstacle > 126)
        return 0;
    if (map->full < 32 || map->full > 126)
        return 0;

    return 1; // 全部校验通过
}