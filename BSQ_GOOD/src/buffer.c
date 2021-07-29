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

void	init_buffer(t_buffer *buffer, int fd)
{
	buffer->fd = fd;
	buffer->cursor = 0;
	buffer->str_size = 0;
}

int	buffer_get_char(t_buffer *buffer)
{
	ssize_t	n_read;
	char	c;

	if (buffer->cursor == buffer->str_size)
	{
		n_read = read(buffer->fd, buffer->buffer, BUFFER_SIZE);
		if (n_read == -1)
			return (READ_ERROR);
		if (n_read == 0)
			return (READ_EOF);
		buffer->str_size = n_read;
		buffer->cursor = 0;
	}
	c = buffer->buffer[buffer->cursor];
	buffer->cursor++;
	return ((int)c);
}

int	buffer_read_line(t_buffer *buffer, char *line, size_t line_size)
{
	int		c;
	size_t	cursor;

	ft_assert(line_size > 0, "buffer_read_line: line size is 0");
	cursor = 0;
	while (true)
	{
		if (cursor >= line_size)
			return (LINE_IS_TOO_LONG);
		c = buffer_get_char(buffer);
		if (c == READ_ERROR)
			return (READ_ERROR);
		if (c == '\n' || c == READ_EOF)
		{
			line[cursor++] = '\0';
			return (0);
		}
		line[cursor++] = c;
	}
}
