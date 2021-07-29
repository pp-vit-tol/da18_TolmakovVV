#include <stdlib.h>

#include "map.h"
#include "ft_assert.h"
#include "ft_stdout.h"

t_map	*new_map(t_legend	*legend)
{
	size_t	i;
	t_map	*map;

	map = malloc(sizeof(*map));
	if (map == NULL)
		return (NULL);
	map->line_len = 0;
	map->n_lines = legend->n_lines;
	if (map->n_lines > INITIAL_MAP_SIZE)
		map->map_size = INITIAL_MAP_SIZE;
	else
		map->map_size = map->n_lines;
	map->map = malloc(sizeof(map->map[0]) * map->map_size);
	if (map->map == NULL)
	{
		free(map);
		return (NULL);
	}
	i = 0;
	while (i < map->map_size)
	{
		map->map[i] = NULL;
		i++;
	}
	return (map);
}

void	delete_map(t_map **map)
{
	size_t	i;

	ft_assert(map != NULL, "delete map: map pointer is null");
	ft_assert(*map != NULL, "delete map: map is null");
	i = 0;
	while (i < (*map)->map_size)
	{
		if ((*map)->map[i] != NULL)
			free((*map)->map[i]);
		(*map)->map[i] = NULL;
		i++;
	}
	free((*map)->map);
	(*map)->map = NULL;
	free(*map);
	*map = NULL;
}

void	calculate_map(t_map *map)
{
	unsigned int	y;
	size_t			x;

	y = map->n_lines - 1;
	while (y > 0)
	{
		y--;
		x = map->line_len - 1;
		while (x > 0)
		{
			x--;
			if (map->map[y][x] == 0)
				continue ;
			map->map[y][x] = map->map[y + 1][x];
			if (map->map[y][x + 1] < map->map[y][x])
				map->map[y][x] = map->map[y][x + 1];
			if (map->map[y + 1][x + 1] < map->map[y][x])
				map->map[y][x] = map->map[y + 1][x + 1];
			map->map[y][x] += 1;
		}
	}
}

t_square	find_square(t_map *map)
{
	unsigned int	y;
	size_t			x;
	t_square		biggest;

	biggest.size = 0;
	y = 0;
	while (y < map->n_lines)
	{
		x = 0;
		while (x < map->line_len)
		{
			if (map->map[y][x] > biggest.size)
			{
				biggest.x = x;
				biggest.y = y;
				biggest.size = map->map[y][x];
			}
			x++;
		}
		y++;
	}
	return (biggest);
}

void	print_map(t_map *map, t_legend *legend, t_square square)
{
	unsigned int	y;
	size_t			x;

	y = 0;
	while (y < map->n_lines)
	{
		x = 0;
		while (x < map->line_len)
		{
			if (map->map[y][x] == 0)
				ft_putchar(legend->obstacle);
			else if (square.y <= y && y < square.y + square.size
				&& square.x <= x && x < square.x + square.size)
				ft_putchar(legend->full);
			else
				ft_putchar(legend->empty);
			x++;
		}
		ft_putchar('\n');
		y++;
	}
}
