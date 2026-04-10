#ifndef BSQ_H
#define BSQ_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_map
{
	int rows;
	int cols;
	char empty;
	char obstacle;
	char full;
	char **grid;
} t_map;

int parse_header(FILE *file, t_map *map);
int read_map(FILE *file, t_map *map);
int validate_map(t_map *map);
void free_map(t_map *map);

int check_line_valid(t_map *map, char *line);

#endif