/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 08:21:43 by dyodlm            #+#    #+#             */
/*   Updated: 2025/04/10 07:46:57 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	check_philos_meals(t_philo *philo)
{
	unsigned long long int	i;

	i = 0;
	(void)i;
	(void)philo;
}

static bool	keep_running(t_philo *philo)
{
	check_philos_meals(philo);
	if (!philo->rules->simulation_stop)
		return (true);
	pthread_mutex_unlock(&philo->rules->stop_mutex);
	return (false);
}

static t_actions	actions(short int i)
{
	static t_actions	actions[] = {
		is_thinking,
		take_left_fork,
		take_right_fork,
		is_eating,
		unlock_the_forks,
		NULL
	};

	return (actions[i]);
}

static bool	look_for_actions_to_do(t_philo *philo)
{
	short int	i;
	bool		alive;
	t_actions	handler;

	i = 0;
	alive = IS_ALIVE;
	while (i < 5)
	{
		handler = actions(i++);
		if (handler)
			alive = handler(philo);
		if (alive == HAS_STARVED)
			break ;
	}
	return (alive);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (1)
	{
		pthread_mutex_lock(&philo->rules->stop_mutex);
		if (!keep_running(philo))
			break ;
		pthread_mutex_unlock(&philo->rules->stop_mutex);
		if (!look_for_actions_to_do(philo))
			return (exit_display(-1), NULL);
		usleep(philo->rules->time_to_sleep * 1000);
	}
	return (NULL);
}
