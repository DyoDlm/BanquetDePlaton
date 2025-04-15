/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 08:21:43 by dyodlm            #+#    #+#             */
/*   Updated: 2025/04/15 11:49:26 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static bool	keep_running(t_philo *philo)
{
	bool	running;

	running = !philo->rules->simulation_stop;
	return (running);
}

static t_actions	actions(short int i)
{
	static t_actions	actions[] = {
		is_thinking,
		take_forks,
		is_eating,
		unlock_the_forks,
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
	while (keep_running(philo))
		look_for_actions_to_do(philo);
	return (NULL);
}
