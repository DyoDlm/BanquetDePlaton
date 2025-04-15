/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_monitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 11:37:48 by dyodlm            #+#    #+#             */
/*   Updated: 2025/04/15 13:51:19 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void *monitor_routine(void *arg)
{
	t_rules *rules = (t_rules *)arg;
	unsigned long long now;
	size_t i;

	while (!rules->simulation_stop)
	{
		i = 0;
		now = get_time_value();
		while (i < rules->num_philo)
		{
			if (!rules->philos[i].is_full &&
				(now - rules->philos[i].last_meal > rules->time_to_die))
			{
				rules->simulation_stop = true;
				pthread_mutex_lock(&rules->print_mutex);
				printf("%llu %d died\n", now - rules->start_time, rules->philos[i].id);
				printf("last eat was : %llu\n", rules->philos[i].last_meal - rules->start_time);
				pthread_mutex_unlock(&rules->print_mutex);
				return NULL;
			}
			i++;
		}
		if (rules->max_eat > 0 && rules->philos_fullfilled == rules->num_philo)
		{
			rules->simulation_stop = true;
			pthread_mutex_lock(&rules->print_mutex);
			printf("ALL PHILOSOPHERS HAVE EATEN ENOUGH\n");
			pthread_mutex_unlock(&rules->print_mutex);
			return NULL;
		}
		usleep(1000);
	}
	return NULL;
}
