#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

#include "map.h"
#include "buffer.h"
#include "ft_assert.h"
#include "errors.h"
#include "ft_string.h"
#include "ft_parse_number.h"
#include "ft_realloc.h"
#include "buffer.h"

#define LEGEND_LEN 16
#define INITIAL_LINE_SIZE 128

int	buffer_read_legend(t_buffer *buffer, t_legend *legend)
{
	char	line[LEGEND_LEN];
	int		read_line_result;
	size_t	line_len;

	read_line_result = buffer_read_line(buffer, line, 14);
	if (read_line_result == LINE_IS_TOO_LONG)
		return (INVALID_MAP);
	if (read_line_result == READ_ERROR)
		return (READ_ERROR);
	line_len = ft_strlen(line);
	if (line_len < 4)
		return (INVALID_MAP);
	legend->empty = line[line_len - 3];
	legend->obstacle = line[line_len - 2];
	legend->full = line[line_len - 1];
	if (legend->empty == legend->obstacle || legend->obstacle == legend->full
		|| legend->full == legend->empty)
		return (INVALID_MAP);
	if (!(legend->empty >= 0x20 && legend->empty <= 0x7e)
		|| !(legend->obstacle >= 0x20 && legend->obstacle <= 0x7e)
		|| !(legend->full >= 0x20 && legend->full <= 0x7e))
		return (INVALID_MAP);
	return (ft_parse_number(line, line_len - 3, &legend->n_lines));
}

int	manage_line_buffer_size(unsigned int **line,
	size_t *line_size, size_t cursor)
{
	int		realloc_result;
	size_t	new_line_size;

	if (*line == NULL)
	{
		*line = malloc(sizeof(unsigned int) * *line_size);
		if (*line == NULL)
			return (ALLOC_ERROR);
	}
	if (cursor >= *line_size)
	{
		new_line_size = *line_size * 2;
		realloc_result = ft_realloc((void **)line,
				sizeof(unsigned int) * *line_size,
				sizeof(unsigned int) * new_line_size);
		if (realloc_result == ALLOC_ERROR)
			return (ALLOC_ERROR);
		*line_size = new_line_size;
	}
	return (0);
}

int	buffer_read_map_line(t_buffer *buffer, t_legend *legend,
	unsigned int **line, size_t *line_len)
{
	int				c;
	size_t			line_size;
	size_t			cursor;

	cursor = 0;
	line_size = INITIAL_LINE_SIZE;
	while (true)
	{
		if (manage_line_buffer_size(line, &line_size, cursor) == ALLOC_ERROR)
			return (ALLOC_ERROR);
		c = buffer_get_char(buffer);
		if (c == READ_ERROR)
			return (READ_ERROR);
		if (c == legend->empty)
			(*line)[cursor] = 1;
		else if (c == legend->obstacle)
			(*line)[cursor] = 0;
		else if (c == '\n' || c == READ_EOF)
			break ;
		else
			return (INVALID_MAP);
		cursor++;
	}
	*line_len = cursor;
	return (0);
}

int	grow_map(t_map *map)
{
	int		realloc_result;
	size_t	new_size;
	size_t	i;

	new_size = map->map_size * 2;
	realloc_result = ft_realloc((void **)&map->map,
			sizeof(map->map[0]) * map->map_size,
			sizeof(map->map[0]) * new_size);
	if (realloc_result == ALLOC_ERROR)
		return (ALLOC_ERROR);
	i = map->map_size;
	while (i < new_size)
	{
		map->map[i] = NULL;
		i++;
	}
	map->map_size = new_size;
	return (0);
}

int	buffer_read_map(t_buffer *buffer, t_legend *legend, t_map	*map)
{
	size_t	i;
	ssize_t	len;
	size_t	line_len;
	int		result;

	i = 0;
	len = -1;
	while (i < map->n_lines)
	{
		if (i >= map->map_size && grow_map(map) == ALLOC_ERROR)
			return (ALLOC_ERROR);
		result = buffer_read_map_line(buffer, legend,
				&map->map[i], &line_len);
		if (result != 0)
			return (result);
		if (len == -1)
			len = line_len;
		else if (len != (ssize_t)line_len)
			return (INVALID_MAP);
		i++;
	}
	map->line_len = len;
	return (0);
}
