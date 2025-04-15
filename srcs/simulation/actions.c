/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 08:29:32 by dyodlm            #+#    #+#             */
/*   Updated: 2025/04/15 12:17:19 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void is_eating(t_philo *philo)
{
	philo->meals_eaten++;
	if (philo->rules->max_eat > 0 &&
		philo->meals_eaten >= philo->rules->max_eat &&
		!philo->is_full)
	{
		philo->is_full = true;
		philo->rules->philos_fullfilled++;
	}
	if (!philo->rules->simulation_stop)
		print_action(philo, "IS EATING");
	philo->last_meal = get_time_value();
	usleep(philo->rules->time_to_eat * 1000);
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
	if (!philo->rules->simulation_stop)
	{
		print_action(philo, "TAKING LEFT FORK");
		print_action(philo, "TAKING RIGHT FORK");
	}
}

void	unlock_the_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	print_action(philo, "IS SLEEPING");
	usleep(philo->rules->time_to_sleep * 1000);
}
