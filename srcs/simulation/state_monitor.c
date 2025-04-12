/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_monitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 11:37:48 by dyodlm            #+#    #+#             */
/*   Updated: 2025/04/12 07:43:40 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	display_fullfilled_philos(t_rules *rules)
{
	pthread_mutex_lock(&rules->stop_mutex);
	rules->dead_philo.simulation_stop = 1;
	pthread_mutex_unlock(&rules->stop_mutex);
	pthread_mutex_unlock(&rules->full_mutex);
	printf("ALL PHILOSOPHERS HAVE EATEN ENOUGH\n");
}

static void	display_dead_philo(t_rules *rules, int id)
{
	long	time;

	time = get_time_value() - rules->start_time;
	pthread_mutex_lock(&rules->stop_mutex);
	rules->dead_philo.simulation_stop = 1;
	pthread_mutex_unlock(&rules->stop_mutex);
	if (rules->dead_philo.simulation_stop)
		printf("A PHILO DIED\nDEATH TIME : %ld ms\nID : %d\n",
			time, id);
}

void	*monitor_routine(void *arg)
{
	t_rules					*rules;
	unsigned long long int	i;

	i = 0;
	rules = (t_rules *)arg;
	while (1)
	{
		usleep(1000);
		pthread_mutex_lock(&rules->full_mutex);
		if (rules->philos_fullfilled >= rules->num_philo)
			return (display_fullfilled_philos(rules), NULL);
		pthread_mutex_unlock(&rules->full_mutex);
		i = 0;
		while (i < rules->num_philo)
		{
			if ((get_time_value() - rules->philos[i].last_meal)
				> rules->time_to_die)
				return (display_dead_philo(rules, i), NULL);
			i++;
		}
	}
	return (NULL);
}
