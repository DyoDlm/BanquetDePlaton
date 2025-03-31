#include "philosophers.h"

void	fd_putchar(int c, int fd)
{
	write(fd, &c, 1);
}

void	fd_putstr(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i])
		fd_putchar(s[i++], fd);
}
