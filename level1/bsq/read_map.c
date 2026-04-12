#include "bsq.h"

/**
 * 读取地图主体内容并存储到二维数组
 * 逻辑：逐行读取 -> 去换行 -> 校验长度 -> 分配内存并拷贝 -> 检查多余行
 * 返回值：1 成功，0 失败（触发 map error）
 */
int read_map(FILE *file, t_map *map)
{
	char *line = NULL;	// 用于 getline 的临时缓冲区
	size_t buf_len = 0; // getline 自动维护的缓冲区大小
	ssize_t r;			// 存储 getline 实际读到的字符数

	// --- 1. 为行指针数组分配内存 ---
	// 分配 (rows + 1) 个空间，最后一个位置设为 NULL，方便后续遍历和释放
	map->grid = malloc((map->rows + 1) * sizeof(char *));
	if (!map->grid)
		return (0);

	for (int i = 0; i < map->rows; i++)
	{
		// 逐行读取文件内容
		r = getline(&line, &buf_len, file);
		// 如果读到一半发现文件提前结束（实际行数 < Header 声明行数），报错
		if (r == -1)
		{
			free(line);
			return (0);
		}

		// --- 2. 手动清理换行符并计算该行实际字符数 ---
		int cur_cols = 0;
		// 停止条件：遇到字符串结束符 \0 或换行符 \n \r
		while (line[cur_cols] && line[cur_cols] != '\n' && line[cur_cols] != '\r')
			cur_cols++;
		// 在换行符位置插入 \0，手动截断字符串，使其只包含地图有效字符
		line[cur_cols] = '\0';

		// --- 3. 验证地图合法性：列数一致性 ---
		if (i == 0)
		{
			// 第一行读完后，确定整个地图的基准宽度（列数）
			map->cols = cur_cols;
		}
		else if (cur_cols != map->cols)
		{
			// 如果后续任意一行的长度与第一行不等，视为非法地图
			free(line);
			return (0);
		}

		// --- 4. 验证地图合法性：空地图检查 ---
		// 如果某行没有任何有效字符（例如直接一个换行符），则视为非法
		if (map->cols == 0)
		{
			free(line);
			return (0);
		}

		// --- 5. 存储当前行数据 (手动实现 strdup) ---
		// 申请 (cols + 1) 空间，包含末尾的 '\0'
		map->grid[i] = malloc(sizeof(char) * (map->cols + 1));
		if (!map->grid[i])
		{
			free(line);
			return (0);
		}

		// 将临时缓冲区 line 中的内容拷贝到持久化的 grid[i] 中
		for (int j = 0; j <= map->cols; j++)
			map->grid[i][j] = line[j];
	}

	// --- 6. 设置结束标志并清理 ---
	map->grid[map->rows] = NULL;

	// 关键校验：检查文件是否还有多余的行
	// 如果 Header 声明 9 行，但文件实际上有 10 行或更多，也是非法地图
	while ((r = getline(&line, &buf_len, file)) != -1)
	{
		int i = 0;
		while (line[i] == '\n' || line[i] == '\r')
			i++;
		if (line[i] != '\0')
		{
			free(line);
			return (0);
		}
	}

	// 释放由 getline 动态申请的临时缓冲区内存
	free(line);
	return (1); // 成功加载完整地图
}