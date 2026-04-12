#include "bsq.h"

/**
 * 解析地图文件的第一行配置信息 (Header)
 * 目标：提取行数 (rows) 以及三个关键字符 (empty, obstacle, full)
 * 格式要求：数字与字符之间、字符与字符之间由空格或制表符分隔
 * 返回值：1 (成功), 0 (失败，触发 map error)
 */
int parse_header(FILE *file, t_map *map)
{
    char    *line = NULL;
    size_t  len = 0;
    ssize_t r;
    int     i = 0;

    // --- 1. 读取首行 ---
    // getline 分配的内存必须在所有退出路径上妥善处理
    r = getline(&line, &len, file);
    if (r <= 0)
        return (0);

    // --- 2. 手动解析行数 (替代 atoi) ---
    map->rows = 0;
    while (line[i] >= '0' && line[i] <= '9')
    {
        // 经典的字符串转整数算法：累乘10并加上当前位数
        map->rows = map->rows * 10 + (line[i] - '0');
        i++;
    }
    
    // 如果 i 没动，说明第一行开头不是数字，格式错误
    if (i == 0)
    {
        free(line);
        return (0);
    }

    // 数字后面必须紧跟空格或制表符，否则说明格式不是 "数字 字符..."
    if (line[i] != ' ' && line[i] != '\t')
    {
        free(line);
        return (0);
    }

    // --- 3. 提取三个核心标记字符 ---

    // 解析 empty (空位字符)
    while (line[i] == ' ' || line[i] == '\t') i++;
    if (!line[i] || line[i] == '\n') { free(line); return (0); }
    map->empty = line[i++];

    // 解析 obstacle (障碍物字符)
    while (line[i] == ' ' || line[i] == '\t') i++;
    if (!line[i] || line[i] == '\n') { free(line); return (0); }
    map->obstacle = line[i++];

    // 解析 full (填充字符)
    while (line[i] == ' ' || line[i] == '\t') i++;
    if (!line[i] || line[i] == '\n') { free(line); return (0); }
    map->full = line[i++];

    // 格式严检查：full 字符后面应该是换行符或字符串结束符
    // 如果后面还有其他杂质字符，说明第一行格式多余，判定为错误
    if (line[i] != '\n' && line[i] != '\r' && line[i] != '\0')
    {
        free(line);
        return (0);
    }

    // --- 4. 内存清理 ---
    // 在进入最终逻辑校验前释放临时缓冲区
    free(line);

    // --- 5. 合法性逻辑校验 ---

    // 5.1 行数必须大于 0
    if (map->rows <= 0)
        return (0);

    // 5.2 字符排他性检查：三个字符必须彼此唯一
    if (map->empty == map->obstacle ||
        map->empty == map->full ||
        map->obstacle == map->full)
        return (0);

    // 5.3 字符范围检查：必须是 ASCII 可打印字符 (32~126)
    // 排除掉控制字符（如 127 DEL 或 0-31 的不可见字符）
    if (map->empty < 32 || map->empty > 126 ||
        map->obstacle < 32 || map->obstacle > 126 ||
        map->full < 32 || map->full > 126)
        return (0);

    return (1); // 校验成功
}