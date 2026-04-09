#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

void print_board(int **board, int width, int height)
{
	int x;
	int y;

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

int count_neighbors(int **board, int x, int y, int w, int h)
{
	int dx;
	int dy;
	int count = 0;

	dy = -1;
	while (dy <= 1)
	{
		dx = -1;
		while (dx <= 1)
		{
			if (!(dx == 0 && dy == 0))
			{
				int nx = x + dx;
				int ny = y + dy;

				if (nx >= 0 && nx < w && ny >= 0 && ny < h)
					count += board[ny][nx];
			}
			dx++;
		}
		dy++;
	}
	return count;
}

void next_gen(int **b, int **n, int w, int h)
{
	int x;
	int y;
	int neighbors;

	y = 0;
	while (y < h)
	{
		x = 0;
		while (x < w)
		{
			neighbors = count_neighbors(b, x, y, w, h);

			if (b[y][x] == 1)
				n[y][x] = (neighbors == 2 || neighbors == 3);
			else
				n[y][x] = (neighbors == 3);

			x++;
		}
		y++;
	}
}

void swap(int ***n1, int ***n2)
{
	int **tmp = *n1;
	*n1 = *n2;
	*n2 = tmp;
}

int main(int argc, char **argv)
{
	// 1 解析参数
	int width;
	int height;
	int iterations;

	if (argc != 4)
		return (1);
	width = atoi(argv[1]);
	height = atoi(argv[2]);
	iterations = atoi(argv[3]);
	if (width <= 0 || height <= 0)
		return (1);

	// 2 创建棋盘
	int **board;
	int **next;
	int i;

	board = malloc(sizeof(int *) * height);
	next = malloc(sizeof(int *) * height);
	if (!board || !next)
		return (1);
	i = 0;
	while (i < height)
	{
		board[i] = calloc(width, sizeof(int));
		next[i] = calloc(width, sizeof(int));
		i++;
	}

	// 3 读取stdin画图

	int x = 0;
	int y = 0;
	int pen = 0;
	char c;
	// 题目隐含逻辑：起点是否染色？
	// 很多类似题目要求：在处理任何指令前，先标记起点
	board[y][x] = pen;

	while (read(0, &c, 1) > 0)
	{
		if (c == 'w')
			y--;
		else if (c == 's')
			y++;
		else if (c == 'a')
			x--;
		else if (c == 'd')
			x++;
		else if (c == 'x')
			pen = !pen;

		if (x < 0)
			x = 0;
		if (x >= width)
			x = width - 1;
		if (y < 0)
			y = 0;
		if (y >= height)
			y = height - 1;

		// 关键：只要 pen 状态是激活的，移动到的位置就要设为 1
		if (pen)
			board[y][x] = 1;
	}

	// 4 运行iterations
	while (iterations)
	{
		next_gen(board, next, width, height);
		swap(&board, &next);
		iterations--;
	}
	// 5 打印棋盘
	print_board(board, width, height);
	for (i = 0; i < height; i++)
	{
		free(board[i]);
		free(next[i]);
	}
	free(board);
	free(next);
	return (0);
}