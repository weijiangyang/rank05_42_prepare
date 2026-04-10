#include "bsq.h"

/**
 * 辅助函数：打印地图
 * 遍历地图的每一行，并将存储在二维数组中的字符串打印出来
 */
void print_map(t_map *map)
{
    for (int i = 0; i < map->rows; i++)
        printf("%s\n", map->grid[i]);
}

/**
 * 程序入口
 * 参数 argc: 命令行参数数量
 * 参数 argv: 命令行参数字符串数组（argv[1] 通常是地图文件路径）
 */
int main(int argc, char **argv)
{
    FILE *file;
    t_map map; // 结构体，通常包含行数、列数、空位字符、障碍物字符、满位字符和二维数组

    // --- 1. 检查参数数量 ---
    // 如果没有提供地图文件路径，直接退出
    if (argc < 2)
        return 1;

    // --- 2. 打开文件 ---
    file = fopen(argv[1], "r");
    if (!file)
    {
        // 文件打开失败（如文件不存在或权限不足）
        return 1;
    }

    // --- 3. 解析文件头 (Header) ---
    // 地图文件的第一行通常包含：行数、空位字符、障碍物字符、满位字符
    // 例如: "9.ox" 表示 9 行，'.' 是空地，'o' 是障碍，'x' 是填充
    if (!parse_header(file, &map))
    {
        fprintf(stderr, "map error\n"); // 输出到标准错误流
        fclose(file); // 退出前记得关闭文件
        return 1;
    }

    // --- 4. 读取地图内容 ---
    // 将文件中的字符读取并存入 map.grid 二维数组中
    if (!read_map(file, &map))
    {
        fprintf(stderr, "map error\n");
        fclose(file);
        return 1;
    }

    // --- 5. 验证地图合法性 ---
    // 检查：每一行的长度是否一致？是否有非法字符？行数是否匹配？
    if (!validate_map(&map))
    {
        fprintf(stderr, "map error\n");
        free_map(&map); // 如果读取过程中分配了内存，需释放
        fclose(file);
        return 1;
    }

    // 调试信息（正式提交时通常需要删掉）
    printf("map is valid!\n");

    // --- 6. 核心逻辑：求解 ---
    // 调用动态规划算法，找到并标记出最大的正方形
    solve_bsq(&map);

    // --- 7. 输出结果 ---
    // 打印处理完（已标记最大正方形）的地图
    print_map(&map);

    // --- 8. 清理现场 ---
    free_map(&map); // 释放 grid 以及相关动态内存
    fclose(file);   // 关闭文件指针

    return 0;
}
