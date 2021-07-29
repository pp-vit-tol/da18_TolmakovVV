#include <stddef.h>

#include "errors.h"

int	ft_parse_number(char *buffer, size_t buffer_len, unsigned int *number)
{
	size_t			i;
	unsigned int	accumulator;

	accumulator = 0;
	i = 0;
	while (i < buffer_len)
	{
		if (!(buffer[i] >= '0' && buffer[i] <= '9'))
			return (INVALID_INT);
		accumulator *= 10;
		accumulator += buffer[i] - '0';
		i++;
	}
	*number = accumulator;
	return (0);
}
