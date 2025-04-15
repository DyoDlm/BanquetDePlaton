/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 12:05:20 by dyodlm            #+#    #+#             */
/*   Updated: 2025/04/15 13:48:37 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

size_t	ft_strlen(char *str)
{
	size_t	len;

	len = 0;
	while (str && str[len])
		len++;
	return (len);
}

bool	ft_isdigit(int c)
{
	return ((c <= '9' && c >= '0'));
}

unsigned long long int	ft_atoull(char *number)
{
	unsigned long long int	n;
	size_t					i;

	n = 0;
	i = 0;
	while (number && ft_isdigit(number[i++]))
		continue ;
	if (ft_strlen(number) != i - 1)
		return (-1);
	i = 0;
	while (number[i] != '\0')
	{
		if (ft_isdigit(number[i]))
			n = n * 10 + (number[i] - '0');
		else
			break ;
		i++;
	}
	return (n);
}
