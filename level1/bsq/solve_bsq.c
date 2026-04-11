#include "bsq.h"
/**
 * 辅助函数：计算三个整数中的最小值
 */
int min3(int a, int b, int c)
{
    int m = a;
    if (b < m)
        m = b;
    if (c < m)
        m = c;
    return m;
}

/**
 * BSQ 核心解题函数
 * 使用动态规划 (Dynamic Programming) 算法
 */
void solve_bsq(t_map *map)
{
    int **dp;       // DP 矩阵，dp[i][j] 表示以 (i, j) 为右下角所能构成的最大正方形的边长
    int max = 0;    // 记录最大正方形的边长
    int max_i = 0;  // 最大正方形右下角的横坐标
    int max_j = 0;  // 最大正方形右下角的纵坐标

    // --- 1. 初始化 DP 矩阵内存 ---
    dp = malloc(sizeof(int *) * map->rows);
    if (!dp)
        return;
    for (int i = 0; i < map->rows; i++)
	{
		dp[i] = malloc(sizeof(int) * map->cols);
		if(!dp[i])
		{
			while(--i >= 0)
				free(dp[i]);
		}
		free(dp);
		return;
	}
        

    // --- 2. 填充 DP 矩阵 ---
    for (int i = 0; i < map->rows; i++)
    {
        for (int j = 0; j < map->cols; j++)
        {
            // 如果当前位置是障碍物，则无法作为正方形的一部分（边长为 0）
            if (map->grid[i][j] == map->obstacle)
                dp[i][j] = 0;
            // 如果在第一行或第一列，且不是障碍物，则最大边长只能是 1
            else if (i == 0 || j == 0)
                dp[i][j] = 1;
            // 状态转移方程：当前点的最大边长取决于其 左、上、左上 三个邻居的最小值 + 1
            else
                dp[i][j] = min3(
                    dp[i-1][j],   // 上方
                    dp[i][j-1],   // 左侧
                    dp[i-1][j-1]  // 左上方
                ) + 1;

            // 实时更新全局最大值及其坐标
            if (dp[i][j] > max)
            {
                max = dp[i][j];
                max_i = i;
                max_j = j;
            }
        }
    }

    // --- 3. 修改原地图，标记最大正方形 ---
    // 根据找到的右下角坐标 (max_i, max_j) 和边长 max，向左上方填充
    for (int i = max_i; i > max_i - max; i--)
    {
        for (int j = max_j; j > max_j - max; j--)
        {
            map->grid[i][j] = map->full; // 使用指定的 'full' 字符替换
        }
    }

    // --- 4. 释放内存 ---
    for (int i = 0; i < map->rows; i++)
        free(dp[i]);
    free(dp);
}