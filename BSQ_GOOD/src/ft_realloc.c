#include <stdlib.h>

#include "errors.h"
#include "ft_assert.h"

void	ft_memcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		dst[i] = src[i];
		i++;
	}
}

int	ft_realloc(void **buffer, size_t old_size, size_t new_size)
{
	void	*new_buffer;

	ft_assert(buffer != NULL, "ft_realloc: buffer pointer is null");
	ft_assert(*buffer != NULL, "ft_realloc: buffer is null");
	new_buffer = malloc(new_size);
	if (new_buffer == NULL)
		return (ALLOC_ERROR);
	ft_memcpy((char *)new_buffer, (char *)*buffer, old_size);
	free(*buffer);
	*buffer = new_buffer;
	return (0);
}
