/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fin.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 07:11:23 by dyodlm            #+#    #+#             */
/*   Updated: 2025/04/08 10:03:05 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	exit_display(int status)
{
	if (status == 0)
		printf("Problem parsing arguments\n");
	else if (status == 123)
		printf("Nicely done, c'est tchao Haha\n");
}

void	cleanup(t_rules *rules)
{
	unsigned long long int	i;

	i = 0;
	while (i < rules->num_philo)
		pthread_mutex_destroy(&rules->forks[i++]);
	free(rules->forks);
	free(rules->philos);
	pthread_mutex_destroy(&rules->print_mutex);
	pthread_mutex_destroy(&rules->stop_mutex);
}
