#include "bsq.h"

/**
 * 从文件中读取地图网格内容并存入 map->grid
 * @param file: 已经跳过 Header 后的文件指针
 * @param map: 存储地图信息的结构体
 * @return: 成功返回 1, 失败返回 0
 */
int read_map(FILE *file, t_map* map)
{
    char* line = NULL; // 临时指针，用于 getline 存储读取的每一行数据
    size_t len = 0;    // getline 需要的缓冲区长度变量

    // --- 1. 为二维数组分配“行”指针内存 ---
    // 分配 (rows + 1) 是为了在最后放一个 NULL，方便后续遍历或作为结束标志
    map->grid = malloc((map->rows + 1) * sizeof(char *));
    if (!map->grid)
        return 0; // 内存分配失败

    // --- 2. 循环读取每一行 ---
    for (int i = 0; i < map->rows; i++)
    {
        // 从文件中读取一行。如果读取结果为 -1，说明文件行数少于 Header 声明的行数
        if (getline(&line, &len, file) == -1)
            return 0;

        // --- 3. 清理换行符 ---
        // strcspn 会找到 "\r\n" 中任意字符第一次出现的位置
        // 将其替换为 '\0'，从而去掉行尾的换行符，保证 grid[i] 只存地图字符
        line[strcspn(line, "\r\n")] = '\0';

        // --- 4. 拷贝并保存当前行 ---
        // strdup 会自动 malloc 足够的空间并将 line 的内容复制过去
        map->grid[i] = strdup(line);
        if (!map->grid[i])
            return 0; // 某行复制失败
    }

    // --- 5. 收尾工作 ---
    // 将数组最后一个元素置为 NULL
    map->grid[map->rows] = NULL;

    // 释放由 getline 自动分配/扩展的缓冲区内存
    free(line);
    
    return 1; // 读取成功
}