#include "bsq.h"

int min3(int a, int b, int c)
{
    int m = a;
    if (b < m)
        m = b;
    if (c < m)
        m = c;
    return m;
}

void solve_bsq(t_map *map)
{
    int **dp;
    int max = 0, max_i = 0, max_j = 0;

    dp = malloc(sizeof(int *) * map->rows);
	if (!dp)
		return;
    for (int i = 0; i < map->rows; i++)
        dp[i] = malloc(sizeof(int) * map->cols);

    for (int i = 0; i < map->rows; i++)
    {
        for (int j = 0; j < map->cols; j++)
        {
            if (map->grid[i][j] == map->obstacle)
                dp[i][j] = 0;
            else if (i == 0 || j == 0)
                dp[i][j] = 1;
            else
                dp[i][j] = min3(
                    dp[i-1][j],
                    dp[i][j-1],
                    dp[i-1][j-1]
                ) + 1;

            if (dp[i][j] > max)
            {
                max = dp[i][j];
                max_i = i;
                max_j = j;
            }
        }
    }

    for (int i = max_i; i > max_i - max; i--)
        for (int j = max_j; j > max_j - max; j--)
            map->grid[i][j] = map->full;

    for (int i = 0; i < map->rows; i++)
        free(dp[i]);
    free(dp);
}