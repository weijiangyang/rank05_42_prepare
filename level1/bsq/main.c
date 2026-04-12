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

static void solve_and_print(FILE *file)
{
	t_map map = {0};//初始化

	// 1. 解析表头
	if (!parse_header(file, &map))
	{
		fprintf(stderr, "map error\n");
		return;
	}

	// --- 4. 读取地图内容 ---
	// 将文件中的字符读取并存入 map.grid 二维数组中
	if (!read_map(file, &map))
	{
		fprintf(stderr, "map error\n");
		free_map(&map);
		return ;
	}

	// --- 5. 验证地图合法性 ---
	// 检查：每一行的长度是否一致？是否有非法字符？行数是否匹配？
	if (!validate_map(&map))
	{
		fprintf(stderr, "map error\n");
		free_map(&map); // 如果读取过程中分配了内存，需释放
		return ;
	}

	// 调试信息（正式提交时通常需要删掉）
	//printf("map is valid!\n");

	// --- 6. 核心逻辑：求解 ---
	// 调用动态规划算法，找到并标记出最大的正方形
	solve_bsq(&map);

	// --- 7. 输出结果 ---
	// 打印处理完（已标记最大正方形）的地图
	print_map(&map);

	// --- 8. 清理现场 ---
	free_map(&map); // 释放 grid 以及相关动态内存
	
}

int main(int argc, char **argv)
{
	if (argc == 1) // 处理标准输入
	{
		solve_and_print(stdin);
	}
	else
	{
		for (int i = 1; i < argc; i++) // 循环处理多个文件
		{
			FILE *file = fopen(argv[i], "r");
			if (file == NULL)
			{
				fprintf(stderr, "map error\n"); // 无法打开文件也是 map error
				continue;
			}
			solve_and_print(file);
			fclose(file);
		}
	}
	return 0;
}
