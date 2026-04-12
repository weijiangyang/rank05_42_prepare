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
static size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}
int parse_header(FILE *file, t_map *map)
{
    char line[1024];
    if (!fgets(line, sizeof(line), file)) return (-1); // 空文件

    int len = ft_strlen(line);
    if (len > 0 && line[len - 1] == '\n') line[--len] = '\0';
    if (len < 4) return (0); // 长度不足以容纳 "1.ox"

    // 最后三个字符固定为 empty, obstacle, full
    map->full = line[len - 1];
    map->obstacle = line[len - 2];
    map->empty = line[len - 3];

    // 前面的部分必须是纯数字
    line[len - 3] = '\0';
    map->rows = ft_atoi(line);

    if (map->rows <= 0 || map->empty == map->obstacle || 
        map->empty == map->full || map->obstacle == map->full)
        return (0);
    return (1);
}