/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 12:05:32 by dyodlm            #+#    #+#             */
/*   Updated: 2025/04/15 11:41:10 by dyodlm           ###   ########.fr       */
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
# include <stdatomic.h>
# include <stddef.h>

# define IS_ALIVE 1
# define HAS_STARVED 0

typedef struct s_rules	t_rules;

typedef struct s_philo
{
	int						id;
	unsigned long long int	meals_eaten;
	unsigned long long int	last_meal;
	bool					is_full;
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
	unsigned long long int	philos_fullfilled;
	pthread_mutex_t			*forks;
	pthread_mutex_t			*souls;
	pthread_mutex_t			print_mutex;
	pthread_mutex_t			stop_mutex;
	pthread_mutex_t			full_mutex;
	t_philo					*philos;
	atomic_bool				simulation_stop;
}	t_rules;

typedef void			(*t_actions)(t_philo *);

long					get_time_value(void);
void					print_action(t_philo *philo, const char *action);
int						init_all(t_rules *rules, int argc, char **argv);
void					*philo_routine(void *arg);
void					*monitor_routine(void *arg);

//	ACTIONS
void					is_eating(t_philo *philo);
void					is_thinking(t_philo *philo);
void					take_forks(t_philo *philo);
void					unlock_the_forks(t_philo *philo);

//	EXIT
void					exit_display(int status);
void					exit_free(t_rules *rules);

//	LIBFT
unsigned long long int	ft_atoull(char *number);
bool					ft_isdigit(int c);
size_t					ft_strlen(char *str);

//	LIBFD
void					fd_putchar(int c, int fd);
void					fd_putstr(char *s, int fd);

#endif
