/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 08:21:43 by dyodlm            #+#    #+#             */
/*   Updated: 2025/04/08 10:22:30 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (1)
	{
		pthread_mutex_lock(&philo->rules->stop_mutex);
		if (philo->rules->simulation_stop)
		{
			pthread_mutex_unlock(&philo->rules->stop_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->rules->stop_mutex);
		print_action(philo, "is thinking");
		pthread_mutex_lock(philo->left_fork);
		print_action(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		print_action(philo, "has taken a fork");
		print_action(philo, "is eating");
		philo->last_meal = get_time_value();
		philo->meals_eaten++;
		usleep(philo->rules->time_to_eat * 1000);
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		print_action(philo, "is sleeping");
		usleep(philo->rules->time_to_sleep * 1000);
	}
	return (NULL);
}

void	start_simulation(t_rules *rules)
{
	unsigned long long int	i;
	pthread_t				monitor;

	i = 0;
	while (i < rules->num_philo)
	{
		rules->philos[i].last_meal = get_time_value();
		pthread_create(&rules->philos[i].thread, NULL,
			philo_routine, &rules->philos[i]);
		i++;
	}
	pthread_create(&monitor, NULL, monitor_routine, rules);
	i = 0;
	while (i < rules->num_philo)
		pthread_join(rules->philos[i++].thread, NULL);
	pthread_join(monitor, NULL);
}
