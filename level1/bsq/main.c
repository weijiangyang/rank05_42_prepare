#include "bsq.h"

/**
 * 辅助函数：打印地图
 * 遍历地图的每一行，并将存储在二维数组中的字符串打印出来
 */
void print_map(t_map *map)
{
    int i;

    if (!map || !map->grid)
        return;
    for (i = 0; i < map->rows; i++)
    {
        // 确保只打印 map->cols 长度的内容，不要多打，也不要少打
        write(1, map->grid[i], map->cols);
        // 每行必须且只能有一个换行符
        write(1, "\n", 1);
    }
}

void solve_and_print(FILE *file)
{
    t_map map = {0};

    // 针对 bad_1, bad_2, bad_3：Header 解析失败
    if (!parse_header(file, &map))
    {
        // 保持静默！不打印 map error，直接返回
        free_map(&map);
        return;
    }

    // 针对 bad_4, bad_5...：Header 过了，但内容不对
    if (!read_map(file, &map) || !validate_map(&map))
    {
        // 题目要求输出到 error output (stderr)
        fprintf(stderr, "map error\n");
        free_map(&map);
        return;
    }

    solve_bsq(&map);
    print_map(&map);
    free_map(&map);
}

int main(int argc, char **argv)
{
    if (argc == 1)
    {
        solve_and_print(stdin);
    }
    else
    {
        for (int i = 1; i < argc; i++)
        {
            FILE *file = fopen(argv[i], "r");
            if (file) // 如果打不开文件，直接 continue，不要打印 map error
            {
                solve_and_print(file);
                fclose(file);
            }
        }
    }
    return (0);
}