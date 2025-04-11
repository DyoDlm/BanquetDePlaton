/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_and_print.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 12:03:50 by dyodlm            #+#    #+#             */
/*   Updated: 2025/04/11 06:07:03 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	get_time_value(void)
{
	struct timeval	time;
	long			value;

	gettimeofday(&time, NULL);
	value = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (value);
}

void	print_action(t_philo *philo, const char *action)
{
	long	now;

	pthread_mutex_lock(&philo->rules->print_mutex);
	pthread_mutex_lock(&philo->rules->stop_mutex);
 	if (!philo->rules->simulation_stop)
	{
		now = get_time_value() - philo->rules->start_time;
		printf("time : %ld\tID : %d\t\tAction : %s\n", now, philo->id, action);
	}
	pthread_mutex_unlock(&philo->rules->stop_mutex);
	pthread_mutex_unlock(&philo->rules->print_mutex);
}
