#ifndef BUFFER_H
# define BUFFER_H

# include <stddef.h>

# include "map.h"

# define BUFFER_SIZE 1024

struct s_buffer {
	int		fd;
	char	buffer[BUFFER_SIZE];
	size_t	cursor;
	size_t	str_size;
};

typedef struct s_buffer	t_buffer;

void	init_buffer(t_buffer *buffer, int fd);

int		buffer_read_map(t_buffer *buffer, t_legend *legend, t_map	*map);

int		buffer_read_legend(t_buffer *buffer, t_legend *legend);

int		buffer_get_char(t_buffer *buffer);

int		buffer_read_line(t_buffer *buffer, char *line, size_t line_size);

#endif
