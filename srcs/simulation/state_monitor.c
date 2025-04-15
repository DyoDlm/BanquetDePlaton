/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_monitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 11:37:48 by dyodlm            #+#    #+#             */
/*   Updated: 2025/04/15 07:54:41 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static bool	check_the_death(t_rules *rules)
{
	unsigned long long int	i;
	long					time;

	i = 0;
	while (i < rules->num_philo)
	{
		time = get_time_value();
		pthread_mutex_lock(&rules->philos[i].self_mutex);
		if ((time - rules->philos[i].last_meal)
			> rules->time_to_die)
		{
			pthread_mutex_unlock(&rules->philos[i].self_mutex);
			pthread_mutex_lock(&rules->stop_mutex);
			rules->dead_philo.simulation_stop = 1;
			pthread_mutex_unlock(&rules->stop_mutex);
			pthread_mutex_lock(&rules->print_mutex);
			printf("died");
			pthread_mutex_unlock(&rules->print_mutex);
			return (false);
		}
		else
			pthread_mutex_unlock(&rules->philos[i].self_mutex);
		i++;
	}
	return (true);
}

void	*monitor_routine(void *arg)
{
	t_rules					*rules;

  rules = (t_rules *)arg;
	while (1)
	{
		usleep(1000);
		pthread_mutex_lock(&rules->full_mutex);
		if (rules->philos_fullfilled >= rules->num_philo)
		{
			pthread_mutex_unlock(&rules->full_mutex);
			pthread_mutex_lock(&rules->stop_mutex);
			rules->dead_philo.simulation_stop = 1;
			pthread_mutex_unlock(&rules->stop_mutex);
			pthread_mutex_lock(&rules->print_mutex);
			printf("ALL PHILOSOPHERS HAVE EATEN ENOUGH\n");
			pthread_mutex_unlock(&rules->print_mutex);
			return (NULL);
		}
		pthread_mutex_unlock(&rules->full_mutex);
		if (!check_the_death(rules))
			return (NULL);
	}
	return (NULL);
}
