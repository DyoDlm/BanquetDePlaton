/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_monitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 11:37:48 by dyodlm            #+#    #+#             */
/*   Updated: 2025/04/16 13:52:32 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static bool	fullfiled_philos(t_rules *rules)
{
	pthread_mutex_lock(&rules->full_mutex);
	if (rules->max_eat > 0 && rules->philos_fullfilled == rules->num_philo)
	{
		pthread_mutex_unlock(&rules->full_mutex);
		rules->simulation_stop = true;
		pthread_mutex_lock(&rules->print_mutex);
		printf("ALL PHILOSOPHERS HAVE EATEN ENOUGH\n");
		pthread_mutex_unlock(&rules->print_mutex);
		return (true);
	}
	else
		pthread_mutex_unlock(&rules->full_mutex);
	usleep(1000);
	return (false);
}

static bool	dead_philo(t_rules *rules)
{
	unsigned long long int	now;
	unsigned long long int	i;

	i = 0;
	now = get_time_value();
	while (i < rules->num_philo)
	{
		pthread_mutex_lock(&rules->full_mutex);
		if (!rules->philos[i].is_full
			&& (now - rules->philos[i].last_meal > rules->time_to_die))
		{
			pthread_mutex_unlock(&rules->full_mutex);
			rules->simulation_stop = true;
			pthread_mutex_lock(&rules->print_mutex);
			printf("dead");
			pthread_mutex_unlock(&rules->print_mutex);
			return (true);
		}
		else
			pthread_mutex_unlock(&rules->full_mutex);
		i++;
	}
	return (false);
}

void	*monitor_routine(void *arg)
{
	t_rules					*rules;

	rules = (t_rules *)arg;
	while (!rules->simulation_stop)
	{
		if (dead_philo(rules))
			return (NULL);
		if (fullfiled_philos(rules))
			return (NULL);
	}
	return (NULL);
}
