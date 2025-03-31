#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <stddef.h>
# include <stdlib.h>
# include <limits.h>
# include <stdbool.h>
# include <signal.h>
# include <sys/time.h>
# include <pthread.h>

#define NC "\e[0m"
#define YELLOW "\e[1;33m"
#define BYELLOW "\e[1;33m"
#define RED "\e[31m"
#define GREEN "\e[32m"

typedef struct s_counter
{
	pthread_mutex_t	count_mutex;
	unsigned int	count;
}	t_counter;

typedef struct s_locks
{
	pthread_mutex_t	lock_1;
	pthread_mutex_t	lock_2;
	unsigned int	count;
}	t_locks;

typedef struct s_long_data
{
	unsigned long long int	feed;
	unsigned long long int	philos;
	unsigned long long int	death_time;
	unsigned long long int	time_to_eat;
	unsigned long long int	time_to_sleep;
}	t_long_data;

typedef struct s_mid_data
{
	unsigned long int	feed;
	unsigned long int	philos;
	unsigned long int	death_time;
	unsigned long int	time_to_eat;
	unsigned long int	time_to_sleep;
}	t_mid_data;

typedef struct s_data
{
	unsigned int	feed;
	unsigned int	philos;
	unsigned int	death_time;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
}	t_data;

typedef struct s_short_data
{
	unsigned short int	feed;
	unsigned short int	philos;
	unsigned short int	death_time;
	unsigned short int	time_to_eat;
	unsigned short int	time_to_sleep;
}	t_short_data;

typedef struct s_long_threads
{
	pthread_mutex_t	**locks;
	pthread_t		**threads;
	t_long_data		limits;
}	t_long_philosophers;

typedef struct s_mid_threads
{
	pthread_mutex_t	**locks;
	pthread_t		**threads;
	t_mid_data		limits;
}	t_mid_philosophers;

typedef struct s_threads
{
	pthread_mutex_t	**locks;
	pthread_t		**threads;
	t_data			limits;
}	t_philosophers;

typedef struct s_short_threads
{
	pthread_mutex_t	**locks;
	pthread_t		**threads;
	t_short_data	limits;
}	t_short_philosophers;

typedef struct s_format_data
{
	t_long_philosophers		long_threads;
	t_mid_philosophers		mid_threads;
	t_philosophers			threads;
	t_short_philosophers	short_threads;
}	t_format;

//	EXIT
void			exit_display(int status);
void			exit_free(t_long_philosophers *philo);

//	LIBFT
long long int	ft_atoi(char *number);
bool			ft_isdigit(int c);
size_t			ft_strlen(char *str);

//	LIBFD
void			fd_putchar(int c, int fd);
void			fd_putstr(char *s, int fd);

#endif
