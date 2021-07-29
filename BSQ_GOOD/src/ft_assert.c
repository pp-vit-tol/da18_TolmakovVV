#include <stdlib.h>

#include "ft_stdout.h"

void	ft_assert(int cond, char *message)
{
	if (cond == 0)
	{
		ft_puterr(message);
		ft_puterr("\n");
		exit(1);
	}
}
