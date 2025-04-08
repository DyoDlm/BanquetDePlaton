/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 12:05:32 by dyodlm            #+#    #+#             */
/*   Updated: 2025/04/08 10:22:02 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdbool.h>

typedef struct s_rules	t_rules;

typedef struct s_philo
{
	int						id;
	unsigned long long int	meals_eaten;
	unsigned long long int	last_meal;
	pthread_t				thread;
	pthread_mutex_t			*left_fork;
	pthread_mutex_t			*right_fork;
	t_rules					*rules;
}	t_philo;

typedef struct s_rules
{
	unsigned long long int	num_philo;
	unsigned long long int	time_to_die;
	unsigned long long int	time_to_eat;
	unsigned long long int	time_to_sleep;
	unsigned long long int	max_eat;
	unsigned long long int	start_time;
	unsigned long long int	simulation_stop;
	pthread_mutex_t			*forks;
	pthread_mutex_t			print_mutex;
	pthread_mutex_t			stop_mutex;
	t_philo					*philos;
}	t_rules;

long					get_time_value(void);
void					print_action(t_philo *philo, const char *action);
int						init_all(t_rules *rules, int argc, char **argv);
void					start_simulation(t_rules *rules);
void					*monitor_routine(void *arg);

//	EXIT
void					exit_display(int status);
void					cleanup(t_rules *rules);

//	LIBFT
unsigned long long int	ft_atoull(char *number);
bool					ft_isdigit(int c);
size_t					ft_strlen(char *str);

//	LIBFD
void					fd_putchar(int c, int fd);
void					fd_putstr(char *s, int fd);

#endif
