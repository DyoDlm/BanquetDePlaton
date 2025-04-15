/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 08:29:32 by dyodlm            #+#    #+#             */
/*   Updated: 2025/04/15 08:40:31 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->self_mutex);
	philo->last_meal = get_time_value();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->self_mutex);
}

void	is_eating(t_philo *philo)
{
	eat(philo);
	if (philo->meals_eaten >= philo->rules->max_eat && !philo->is_full)
	{
		pthread_mutex_lock(&philo->self_mutex);
		philo->is_full = true;
		pthread_mutex_unlock(&philo->self_mutex);
		pthread_mutex_lock(&philo->rules->full_mutex);
		philo->rules->philos_fullfilled++;
		pthread_mutex_unlock(&philo->rules->full_mutex);
	}
	pthread_mutex_lock(&philo->rules->stop_mutex);
	if (!philo->rules->dead_philo.simulation_stop)
	{
		pthread_mutex_unlock(&philo->rules->stop_mutex);
		print_action(philo, "IS EATING");
	}
	else
		pthread_mutex_unlock(&philo->rules->stop_mutex);
	usleep(philo->rules->time_to_eat * 1000);
//	if (philo->id % 2 == 0)
//		usleep(philo->rules->time_to_eat * 1000);
//	else
//		usleep(philo->rules->time_to_eat)
}

void	is_thinking(t_philo *philo)
{
	print_action(philo, "IS THINKING");
}

void	take_forks(t_philo *philo)
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
		pthread_mutex_unlock(&philo->rules->stop_mutex);
		print_action(philo, "TAKING LEFT FORK");
		print_action(philo, "TAKING RIGHT FORK");
	}
	else
		pthread_mutex_unlock(&philo->rules->stop_mutex);
}

void	unlock_the_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	print_action(philo, "IS SLEEPING");
	usleep(philo->rules->time_to_sleep * 1000);
}
