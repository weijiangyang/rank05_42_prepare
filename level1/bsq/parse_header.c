#include "bsq.h"

#include <unistd.h>

int	ft_atoi(const char *str)
{
	int	i;
	int	res;
	int	sign;

	i = 0;
	res = 0;
	sign = 1;
	// 1. 跳过开头的空白字符（空格、换行、制表符等）
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	// 2. 处理正负号
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	// 3. 转换数字
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (res * sign);
}


int parse_header(FILE *file, t_map *map)
{
    char    *line = NULL;
    size_t  len = 0;
    ssize_t read;
    int     i;

    // 1. 读取整行 Header
    read = getline(&line, &len, file);
    if (read <= 0)
    {
        if (line) free(line);
        return (-1); // 空文件，触发静默返回
    }

    // 2. 去掉行末换行符
    i = (int)read;
    if (i > 0 && line[i - 1] == '\n')
        line[--i] = '\0';

    // 3. 基础长度校验：至少要有 "1.ox" (4个字符)
    if (i < 4)
    {
        free(line);
        return (0); // 格式错误，触发 map error
    }

    // 4. 从末尾切分三个字符 (符合 test_charset 要求)
    map->full = line[i - 1];
    map->obstacle = line[i - 2];
    map->empty = line[i - 3];

    // 5. 前面部分转为数字
    line[i - 3] = '\0';
    map->rows = ft_atoi(line);
    free(line); // 记得及时释放 getline 分配的内存

    // 6. 逻辑校验：行数必须为正，且字符不能重复
    if (map->rows <= 0 || map->empty == map->obstacle || 
        map->empty == map->full || map->obstacle == map->full)
    		return (0);
    return (1);
}