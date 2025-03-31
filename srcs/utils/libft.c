/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 12:05:20 by dyodlm            #+#    #+#             */
/*   Updated: 2025/03/31 06:51:44 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

size_t	ft_strlen(char *str)
{
	size_t len;

	len = 0;
	while (str && str[len])
		len++;
	return (len);
}

bool	ft_isdigit(int c)
{
	return ((c <= '9' && c >= '0'));
}

long long int	ft_atoi(char *number)
{
	long long int	n;
	size_t			i;
	int				p;

	i = 0;
	n = 0;
	p = 1;
	while (number && ft_isdigit(number[i++]))
		continue ;
	if (!number || i < ft_strlen(number))
		return (-1);
	while (number && number[--i])
	{
		n *= n + p * (number[i] + '0');
		p *= 10;
	}
	return (n);
}
