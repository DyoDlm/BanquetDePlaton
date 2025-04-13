/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 08:29:32 by dyodlm            #+#    #+#             */
/*   Updated: 2025/04/12 15:38:16 by dyodlm           ###   ########.fr       */
*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	is_eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->rules->full_mutex);
	philo->last_meal = get_time_value();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->rules->full_mutex);
	if (philo->meals_eaten >= philo->rules->max_eat && !philo->is_full)
	{
		philo->is_full = true;
		pthread_mutex_lock(&philo->rules->full_mutex);
		philo->rules->philos_fullfilled++;
		pthread_mutex_unlock(&philo->rules->full_mutex);
	}
	pthread_mutex_unlock(&philo->rules->stop_mutex);
	if (!philo->rules->dead_philo.simulation_stop)
		print_action(philo, "IS EATING");
	usleep(philo->rules->time_to_eat * 1000);
	return (IS_ALIVE);
}

bool	is_thinking(t_philo *philo)
{
	if (!philo->rules->dead_philo.simulation_stop)
		print_action(philo, "IS THINKING");
	return (IS_ALIVE);
}

bool	take_forks(t_philo *philo)
{
  pthread_mutex_t	*first;
	pthread_mutex_t	*second;

	if (philo->left_fork < philo->right_fork)
	{
		first = philo->left_fork;
		second = philo->right_fork;
	}
	else
	{
		first = philo->right_fork;
		second = philo->left_fork;
	}
	pthread_mutex_lock(first);
	pthread_mutex_lock(second);
	pthread_mutex_lock(&philo->rules->stop_mutex);
	if (!philo->rules->dead_philo.simulation_stop)
	{
		print_action(philo, "TAKING LEFT FORK");
		print_action(philo, "TAKING RIGHT FORK");
	}
	pthread_mutex_unlock(&philo->rules->stop_mutex);
	return (IS_ALIVE);
}

bool	unlock_the_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	if (!philo->rules->dead_philo.simulation_stop)
	{
		print_action(philo, "IS SLEEPING");
	}
	pthread_mutex_unlock(&philo->rules->stop_mutex);
	return (IS_ALIVE);
}
