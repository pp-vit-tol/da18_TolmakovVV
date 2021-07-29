#include <unistd.h>

#include "ft_string.h"

void	ft_putf(int fd, const char *str)
{
	size_t	len;

	len = ft_strlen(str);
	write(fd, str, len);
}

void	ft_putchar(char c)
{
	write(STDOUT_FILENO, &c, 1);
}

void	ft_putstr(const char *str)
{
	ft_putf(STDOUT_FILENO, str);
}

void	ft_puterr(const char *str)
{
	ft_putf(STDERR_FILENO, str);
}
