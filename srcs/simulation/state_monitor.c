/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_monitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 11:37:48 by dyodlm            #+#    #+#             */
/*   Updated: 2025/04/11 09:32:57 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void *monitor_routine(void *arg)
{
	t_rules *rules = (t_rules *)arg;
	unsigned long long i;
	while (1)
	{
		usleep(1000);
		pthread_mutex_lock(&rules->full_mutex);
		if (rules->philos_fullfilled >= rules->num_philo)
		{
			pthread_mutex_lock(&rules->stop_mutex);
			rules->simulation_stop = 1;
			pthread_mutex_unlock(&rules->stop_mutex);
			pthread_mutex_unlock(&rules->full_mutex);
			printf("ALL PHILOSOPHERS HAVE EATEN ENOUGH\n");
			return (NULL);
		}
		pthread_mutex_unlock(&rules->full_mutex);
		i = 0;
		while (i < rules->num_philo)
		{
			if ((get_time_value() - rules->philos[i].last_meal) > rules->time_to_die)
			{
				pthread_mutex_lock(&rules->stop_mutex);
				rules->simulation_stop = 1;
				pthread_mutex_unlock(&rules->stop_mutex);
				printf("A PHILO DIED\n");
				return (NULL);
			}
			i++;
		}
	}
	return NULL;
}
