/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debut.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 11:41:59 by dyodlm            #+#    #+#             */
/*   Updated: 2025/04/15 11:48:38 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "philosophers.h"
/*
static void	print_data(t_rules *rules)
{
	printf("Num philo : %lld\n", rules->num_philo);
	printf("Num philo : %lld\n", rules->time_to_die);
	printf("Num philo : %lld\n", rules->time_to_eat);
	printf("Num philo : %lld\n", rules->time_to_eat);
}*/

static bool	are_values_ok(t_rules *rules)
{
	return (rules->num_philo > 0 && rules->time_to_die > 0
		&& rules->time_to_eat > 0 && rules->time_to_sleep > 0
		&& rules->max_eat > 0);
}

static bool	parse_args(t_rules *rules, int ac, char **av)
{
	if (ac != 5 && ac != 6)
		return (0);
	rules->num_philo = ft_atoull(av[1]);
	rules->time_to_die = ft_atoull(av[2]);
	rules->time_to_eat = ft_atoull(av[3]);
	rules->time_to_sleep = ft_atoull(av[4]);
	rules->philos_fullfilled = 0;
	if (ac == 6)
		rules->max_eat = ft_atoull(av[5]);
	else
		rules->max_eat = INT_MAX;
	rules->simulation_stop = false;
	return (are_values_ok(rules));
}

static void	data_distribution(t_rules *rules)
{
	unsigned long long int	i;

	i = 0;
	while (i < rules->num_philo)
	{
		rules->philos[i].id = i + 1;
		rules->philos[i].is_full = false;
		rules->philos[i].last_meal = 0;
		rules->philos[i].meals_eaten = 0;
		rules->philos[i].last_meal = 0;
		rules->philos[i].rules = rules;
		rules->philos[i].left_fork = &rules->forks[i];
		rules->philos[i].right_fork = &rules->forks[(1 + i) % rules->num_philo];
		i++;
	}
}

int	init_all(t_rules *rules, int argc, char **argv)
{
	unsigned long long int	i;

	i = 0;
	if (!parse_args(rules, argc, argv))
		return (0);
	rules->forks = calloc(sizeof(pthread_mutex_t) * rules->num_philo, 1);
	rules->philos = calloc(sizeof(t_philo) * rules->num_philo, 1);
	if (!rules->forks || !rules->philos)
		return (0);
	pthread_mutex_init(&rules->print_mutex, NULL);
	pthread_mutex_init(&rules->full_mutex, NULL);
	while (i < rules->num_philo)
		pthread_mutex_init(&rules->forks[i++], NULL);
	data_distribution(rules);
	rules->start_time = get_time_value();
	return (exit_display(1), 1);
}
