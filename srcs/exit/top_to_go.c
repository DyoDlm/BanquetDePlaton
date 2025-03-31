/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   top_to_go.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 07:11:23 by dyodlm            #+#    #+#             */
/*   Updated: 2025/03/31 07:13:09 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	exit_free(t_long_philosophers *philos)
{
	int	i;

	i = 0;
	while (philos->locks && philos->locks[i])
		pthread_mutex_destroy(philos->locks[i++]);
}
