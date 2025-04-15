/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_monitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 11:37:48 by dyodlm            #+#    #+#             */
/*   Updated: 2025/04/15 15:41:51 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static bool	fullfiled_philos(t_rules *rules)
{
	if (rules->max_eat > 0 && rules->philos_fullfilled == rules->num_philo)
	{
		rules->simulation_stop = true;
		pthread_mutex_lock(&rules->print_mutex);
		printf("ALL PHILOSOPHERS HAVE EATEN ENOUGH\n");
		pthread_mutex_unlock(&rules->print_mutex);
		return (false);
	}
	usleep(1000);
	return (true);
}

void	*monitor_routine(void *arg)
{
	t_rules					*rules;
	unsigned long long int	now;
	size_t					i;

	rules = (t_rules *)arg;
	while (!rules->simulation_stop)
	{
		i = 0;
		now = get_time_value();
		while (i < rules->num_philo)
		{
			if (!rules->philos[i].is_full
				&& (now - rules->philos[i].last_meal > rules->time_to_die))
			{
				rules->simulation_stop = true;
				pthread_mutex_lock(&rules->print_mutex);
				printf("dead");
				pthread_mutex_unlock(&rules->print_mutex);
				printf("DEDEDEDD");
				return (NULL);
			}
			i++;
		}
		if (!fullfiled_philos(rules))
			return (NULL);
	}
	return NULL;
}
