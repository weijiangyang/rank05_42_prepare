#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

/**
 * 打印棋盘
 * 遍历二维数组，1 打印 'O'，0 打印空格 ' '
 * 注意：每行末尾必须有 '\n'，这是为了配合 cat -e 查看结尾
 */
void print_board(int **board, int width, int height)
{
    int x, y;

    y = 0;
    while (y < height)
    {
        x = 0;
        while (x < width)
        {
            if (board[y][x])
                putchar('O');
            else
                putchar(' ');
            x++;
        }
        putchar('\n');
        y++;
    }
}

/**
 * 计算邻居数量
 * 检查当前格 (x, y) 周围 8 个格子的状态
 * 必须包含边界检查，确保 nx, ny 不越界
 */
int count_neighbors(int **board, int x, int y, int w, int h)
{
    int dx, dy, count = 0;

    dy = -1;
    while (dy <= 1)
    {
        dx = -1;
        while (dx <= 1)
        {
            // 跳过自身 (0, 0)
            if (!(dx == 0 && dy == 0))
            {
                int nx = x + dx;
                int ny = y + dy;

                // 只有在棋盘范围内的邻居才计数
                if (nx >= 0 && nx < w && ny >= 0 && ny < h)
                    count += board[ny][nx];
            }
            dx++;
        }
        dy++;
    }
    return count;
}

/**
 * 生成下一代 (生命游戏核心算法)
 * b: 当前代 (current), n: 下一代 (next)
 */
void next_gen(int **b, int **n, int w, int h)
{
    int x, y, neighbors;

    y = 0;
    while (y < h)
    {
        x = 0;
        while (x < w)
        {
            neighbors = count_neighbors(b, x, y, w, h);
            if (b[y][x] == 1)
                // 存活条件：邻居为 2 或 3
                n[y][x] = (neighbors == 2 || neighbors == 3);
            else
                // 诞生条件：邻居恰好为 3
                n[y][x] = (neighbors == 3);
            x++;
        }
        y++;
    }
}

/**
 * 交换指针
 * 使用三级指针直接修改 main 函数中 board 和 next 指针的指向
 * 这样可以避免昂贵的内存拷贝
 */
void swap(int ***n1, int ***n2)
{
    int **tmp = *n1;
    *n1 = *n2;
    *n2 = tmp;
}

int main(int argc, char **argv)
{
    // 1. 参数校验
    if (argc != 4)
        return (1);

    int width = atoi(argv[1]);
    int height = atoi(argv[2]);
    int iterations = atoi(argv[3]);

    if (width <= 0 || height <= 0)
        return (1);

    // 2. 内存分配
    // 使用 calloc 确保初始化时棋盘所有格子均为 0 (死)
    int **board = malloc(sizeof(int *) * height);
    int **next = malloc(sizeof(int *) * height);
    if (!board || !next) return (1);

    int i = 0;
    while (i < height)
    {
        board[i] = calloc(width, sizeof(int));
        next[i] = calloc(width, sizeof(int));
        i++;
    }

    // 3. 读取 stdin 进行画图 (关键逻辑修正)
    int x = 0, y = 0, pen = 0;
    char c;

    // 重点：根据 Example，x 指令是“切换”开关。
    // 如果初始 pen 是 0，那么在按下第一个 'x' 之前，
    // 所有的 w/a/s/d 移动都不应该在 board 上画出 'O'。
    while (read(0, &c, 1) > 0)
    {
        if (c == 'x')
            pen = !pen;
        else if (c == 'w') y--;
        else if (c == 's') y++;
        else if (c == 'a') x--;
        else if (c == 'd') x++;
        else continue; // 忽略其他字符如 '\n'

        // 边界保护：限制坐标在棋盘内
        if (x < 0) x = 0;
        if (x >= width) x = width - 1;
        if (y < 0) y = 0;
        if (y >= height) y = height - 1;

        // 如果此时画笔是放下的 (pen == 1)，标记当前格子
        if (pen)
            board[y][x] = 1;
    }

    // 4. 演化模拟
    while (iterations > 0)
    {
        next_gen(board, next, width, height);
        swap(&board, &next); // 交换后，最新的结果始终在 board 指针中
        iterations--;
    }

    // 5. 输出结果
    print_board(board, width, height);

    // 6. 清理内存
    i = 0;
    while (i < height)
    {
        free(board[i]);
        free(next[i]);
        i++;
    }
    free(board);
    free(next);

    return (0);
}