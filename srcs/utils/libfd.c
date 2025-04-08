/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libfd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 12:04:06 by dyodlm            #+#    #+#             */
/*   Updated: 2025/04/07 12:04:32 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
