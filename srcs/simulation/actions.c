/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 08:29:32 by dyodlm            #+#    #+#             */
/*   Updated: 2025/04/15 15:33:06 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	safe_sleep(unsigned long long duration, t_rules *rules)
{
	unsigned long long int	start;

	start = get_time_value();
	while (!rules->simulation_stop)
	{
		if (get_time_value() - start >= duration)
			break ;
		usleep(500);
	}
}

void	is_eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->rules->full_mutex);
	philo->meals_eaten++;
	if (philo->rules->max_eat > 0 && philo->meals_eaten
		>= philo->rules->max_eat && !philo->is_full)
	{
		philo->is_full = true;
		philo->rules->philos_fullfilled++;
	}
	if (!philo->rules->simulation_stop)
		print_action(philo, "IS EATING");
	philo->last_meal = get_time_value();
	pthread_mutex_unlock(&philo->rules->full_mutex);
	safe_sleep(philo->rules->time_to_eat, philo->rules);
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
	safe_sleep(philo->rules->time_to_sleep, philo->rules);
}
