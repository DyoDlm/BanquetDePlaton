/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 08:29:32 by dyodlm            #+#    #+#             */
/*   Updated: 2025/04/10 07:49:38 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	is_eating(t_philo *philo)
{
//	if (philo->meals_eaten >= philo->rules->max_eat)
//		return (IS_ALIVE);
//	if (philo->last_meal >= philo->rules->time_to_eat)
//		return (HAS_STARVED);
	print_action(philo, "IS EATING");
	philo->last_meal = get_time_value();
	philo->meals_eaten++;
	usleep(philo->rules->time_to_eat * 1000);
	return (IS_ALIVE);
}

bool	is_thinking(t_philo *philo)
{
	print_action(philo, "IS THINKING");
	return (IS_ALIVE);
}

bool	take_left_fork(t_philo *philo)
{
	print_action(philo, "TAKING LEFT FORK");
	pthread_mutex_lock(philo->left_fork);
	return (IS_ALIVE);
}

bool	take_right_fork(t_philo *philo)
{
	print_action(philo, "TAKING RIGHT FORK");
	pthread_mutex_lock(philo->right_fork);
	return (IS_ALIVE);
}

bool	unlock_the_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	print_action(philo, "IS SLEEPING");
	return (IS_ALIVE);
}
