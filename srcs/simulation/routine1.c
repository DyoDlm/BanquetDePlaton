/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 08:21:43 by dyodlm            #+#    #+#             */
/*   Updated: 2025/04/15 14:10:03 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
/*static bool	keep_running(t_philo *philo)
{
	bool	running;

	running = !philo->rules->simulation_stop;
	return (running);
}

static t_actions	actions(short int i)
{
	static t_actions	actions[] = {
		take_forks,
		is_eating,
		unlock_the_forks,
		is_thinking,
		NULL
	};

	return (actions[i]);
}

static void	look_for_actions_to_do(t_philo *philo)
{
	short int	i;
	t_actions	handler;

	i = 0;
	while (i < 4)
	{
handler = actions(i++);
		if (handler)
			handler(philo);
	}
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (!philo->rules->simulation_stop)
	{
		take_forks(philo);
		is_eating(philo);
		unlock_the_forks(philo);
		is_thinking(philo);
	}
	return (NULL);
}*/

void	*philo_routine(void *arg)
{
	t_philo	*philo = (t_philo *)arg;

	if (philo->id % 2 == 0)
		usleep(1000); // décaler les philosophes pairs

	while (!philo->rules->simulation_stop)
	{
		// Prendre les fourchettes
		pthread_mutex_lock(philo->left_fork);
		print_action(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		print_action(philo, "has taken a fork");

		// Manger
		print_action(philo, "is eating");
		philo->last_meal = get_time_value();
		philo->meals_eaten++;
		safe_sleep(philo->rules->time_to_eat, philo->rules);

		// Poser les fourchettes
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);

		// S'il a fini de manger assez de fois
		if (philo->meals_eaten >= philo->rules->max_eat && !philo->is_full)
		{
			philo->is_full = true;
			pthread_mutex_lock(&philo->rules->full_mutex);
			philo->rules->philos_fullfilled++;
			pthread_mutex_unlock(&philo->rules->full_mutex);
		}

		// Dormir
		print_action(philo, "is sleeping");
		safe_sleep(philo->rules->time_to_sleep, philo->rules);

		// Penser
		print_action(philo, "is thinking");
	}
	return (NULL);
}
