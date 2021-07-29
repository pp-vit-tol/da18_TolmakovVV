#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

#include "buffer.h"
#include "map.h"
#include "ft_stdout.h"
#include "errors.h"

int		driver_internal(int fd);

void	driver(int fd);

int	main(int argc, char *argv[])
{
	int	i;
	int	fd;

	if (argc >= 2)
	{
		i = 1;
		while (i < argc)
		{
			fd = open(argv[i], O_RDONLY);
			driver(fd);
			close(fd);
			i++;
		}
	}
	else
		driver(0);
}

void	driver(int fd)
{
	int	err_code;

	if (fd < 0)
	{
		ft_puterr("map error\n");
		return ;
	}
	err_code = driver_internal(fd);
	if (err_code != 0)
	{
		if (err_code == READ_EOF)
			ft_puterr("map error\n");
		else if (err_code == READ_ERROR)
			ft_puterr("map error\n");
		else if (err_code == INVALID_MAP)
			ft_puterr("map error\n");
		else if (err_code == LINE_IS_TOO_LONG)
			ft_puterr("map error\n");
		else if (err_code == ALLOC_ERROR)
			ft_puterr("error: malloc returned NULL\n");
		else if (err_code == INVALID_INT)
			ft_puterr("map error\n");
		else
			ft_puterr("map error\n");
	}
}

int	driver_internal(int fd)
{
	int			result;
	t_legend	legend;
	t_buffer	buffer;
	t_map		*map;

	init_buffer(&buffer, fd);
	result = buffer_read_legend(&buffer, &legend);
	if (result != 0)
		return (result);
	map = new_map(&legend);
	if (map == NULL)
		return (ALLOC_ERROR);
	result = buffer_read_map(&buffer, &legend, map);
	if (result != 0 || map->n_lines == 0 || map->line_len == 0)
	{
		if (map->n_lines == 0 || map->line_len == 0)
			result = INVALID_MAP;
		delete_map(&map);
		return (result);
	}
	calculate_map(map);
	print_map(map, &legend, find_square(map));
	delete_map(&map);
	return (0);
}
