/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fin.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 07:11:23 by dyodlm            #+#    #+#             */
/*   Updated: 2025/04/16 13:48:32 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	exit_display(int status)
{
	if (status == 0)
		printf("Problem parsing arguments\n");
	else if (status == 123)
		printf("Nicely done, c'est tchao Haha\n");
	else if (status == -1)
		printf("A philosopher is Dead\n");
}

void	exit_free(t_rules *rules)
{
	unsigned long long int	i;

	i = 0;
	while (i < rules->num_philo)
		pthread_mutex_destroy(&rules->forks[i++]);
	free(rules->forks);
	free(rules->philos);
	pthread_mutex_destroy(&rules->full_mutex);
	pthread_mutex_destroy(&rules->print_mutex);
}
