/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_and_print.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 12:03:50 by dyodlm            #+#    #+#             */
/*   Updated: 2025/04/15 14:09:27 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

unsigned long long get_time_value(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000ULL) + (tv.tv_usec / 1000ULL));
}

void	safe_sleep(unsigned long long time, t_rules *rules)
{
	unsigned long long	start;

	start = get_time_value();
	while (!rules->simulation_stop)
	{
		if (get_time_value() - start >= time)
			break;
		usleep(100);
	}
}

void	print_action(t_philo *philo, const char *msg)
{
	pthread_mutex_lock(&philo->rules->print_mutex);
	if (!philo->rules->simulation_stop)
		printf("%llu %d %s\n", get_time_value() - philo->rules->start_time, philo->id, msg);
	pthread_mutex_unlock(&philo->rules->print_mutex);
}
