/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 11:53:29 by dyodlm            #+#    #+#             */
/*   Updated: 2025/04/16 13:42:23 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	start_simulation(t_rules *rules)
{
	unsigned long long int	i;
	pthread_t				monitor;

	i = 0;
	while (i < rules->num_philo)
	{
		rules->philos[i].last_meal = get_time_value();
		pthread_create(&rules->philos[i].thread, NULL,
			philo_routine, &rules->philos[i]);
		i++;
	}
	pthread_create(&monitor, NULL, monitor_routine, rules);
	i = 0;
	while (i < rules->num_philo)
		pthread_join(rules->philos[i++].thread, NULL);
	pthread_join(monitor, NULL);
}

int	main(int ac, char **av)
{
	t_rules	rules;
	int		status;

	status = init_all(&rules, ac, av);
	if (!status)
		return (exit_display(status), 1);
	start_simulation(&rules);
	exit_free(&rules);
	return (0);
}
