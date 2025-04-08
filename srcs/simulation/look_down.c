/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   look_down.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 11:37:48 by dyodlm            #+#    #+#             */
/*   Updated: 2025/04/07 12:12:43 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*monitor_routine(void *arg)
{
	t_rules					*rules;
	unsigned long long int	i;

	rules = (t_rules *)arg;
	while (1)
	{
		i = 0;
		usleep(1000);
		while (i < rules->num_philo)
		{
			if ((timestamp() - rules->philos[i].last_meal) > rules->time_to_die)
			{
				pthread_mutex_lock(&rules->stop_mutex);
				rules->simulation_stop = 1;
				pthread_mutex_unlock(&rules->stop_mutex);
				print_action(&rules->philos[i], "died");
				return (NULL);
			}
			i++;
		}
	}
	return (NULL);
}
