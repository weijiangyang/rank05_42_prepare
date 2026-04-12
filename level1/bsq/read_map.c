#include "bsq.h"

int read_map(FILE *file, t_map *map)
{
    char    *line = NULL;
    size_t  buf_len = 0;
    ssize_t r;

    map->grid = malloc((map->rows + 1) * sizeof(char *));
    if (!map->grid) return (0);

    for (int i = 0; i < map->rows; i++)
    {
        r = getline(&line, &buf_len, file);
        if (r == -1) { free(line); return (0); }

        // --- 1. 手动清理换行符并获取当前行实际长度 ---
        int cur_cols = 0;
        while (line[cur_cols] && line[cur_cols] != '\n' && line[cur_cols] != '\r')
            cur_cols++;
        line[cur_cols] = '\0'; // 截断

        // --- 2. 验证地图合法性：列数一致性 ---
        if (i == 0)
            map->cols = cur_cols; // 记录第一行的长度作为标准
        else if (cur_cols != map->cols)
        {
            free(line);
            return (0); // 长度不一，触发 map error
        }
        
        // --- 3. 验证地图合法性：空行检查 ---
        if (map->cols == 0) { free(line); return (0); }

        // --- 4. 手动实现 strdup 的功能 ---
        map->grid[i] = malloc(sizeof(char) * (map->cols + 1));
        if (!map->grid[i]) { free(line); return (0); }
        
        for (int j = 0; j <= map->cols; j++) // 复制内容（包含 '\0'）
            map->grid[i][j] = line[j];
    }

    map->grid[map->rows] = NULL;
    free(line);
    
    // 检查文件是否还有多余的行（题目要求行数必须严格匹配）
    // 如果 Header 说有 9 行，但文件有 10 行，也算 map error
    if (getline(&line, &buf_len, file) != -1)
    {
        free(line);
        return (0);
    }

    free(line);
    return (1);
}