#include "philosophers.h"

#define ERROR -1
#define SHORT 0
#define STANDARD 1
#define MID 2
#define LONG 3

static bool	check_values_ok(t_long_data limits)
{
	return (!(limits.death_time <= 0
			|| limits.philos <= 0
			|| limits.time_to_eat <= 0
			|| limits.time_to_sleep <= 0));
}

static short int	get_good_allocation(
	char **av,
	int ac,
	t_format *format
	)
{
	short int	i;

	i = 1;
	if (ac < 5 || ac > 6)
		return (ERROR);
	format->long_threads.limits.philos = ft_atoi(av[i++]);
	format->long_threads.limits.death_time = ft_atoi(av[i++]);
	format->long_threads.limits.time_to_eat = ft_atoi(av[i++]);
	format->long_threads.limits.time_to_sleep = ft_atoi(av[i++]);
	if (av[i])
		format->long_threads.limits.feed = ft_atoi(av[i]);
	if (!check_values_ok(format->long_threads.limits))
		return (ERROR);
	return (LONG);
}

static void	init_routines(
	t_long_data limits,
	pthread_t ***threads,
	pthread_mutex_t ***locks
	)
{
	(void)threads;
	(void)limits;
	(void)locks;
}

static bool	apply_routines(t_format *buffer)
{
	t_long_philosophers	data;

	data = buffer->long_threads;
	init_routines(data.limits, &data.threads, &data.locks);
	return (true);
}

static void	assemble_threads(t_long_philosophers *philos)
{
	int	i;

	i = 0;
	while (philos->threads && philos->threads[i])
		pthread_join(*philos->threads[i++], NULL);
}

int	main(int ac, char **av)
{
	t_format	buffer;
	int			size;

	memset(&buffer, 0, sizeof(t_format));
	size = get_good_allocation(av, ac, &buffer);
	if (size == ERROR || !apply_routines(&buffer))
		return (exit_display(0), 0);
	return (exit_display(1), 1);
	assemble_threads(&buffer.long_threads);
	exit_free(&buffer.long_threads);
	return (exit_display(1), 1);
}
/*
static void	*thread_routine1(void *data)
{
	t_locks		*locks;

	locks = (t_locks *)data;
	pthread_mutex_lock(&locks->lock_1);
	pthread_mutex_lock(&locks->lock_2);
	locks->count += 1;
	pthread_mutex_unlock(&locks->lock_2);
	pthread_mutex_unlock(&locks->lock_1);
	return (NULL);
}

void *thread_routine2(void *data)
{
	t_locks		*locks;

	locks = (t_locks *)data;
	pthread_mutex_lock(&locks->lock_2);
	pthread_mutex_lock(&locks->lock_1);
	locks->count += 1;
	pthread_mutex_unlock(&locks->lock_1);
	pthread_mutex_unlock(&locks->lock_2);
	return (NULL);
}

int	main()
{
	pthread_t	tid1;
	pthread_t	tid2;
	t_locks		locks;

	locks.count = 0;
	pthread_mutex_init(&locks.lock_1, NULL);
	pthread_mutex_init(&locks.lock_2, NULL);
	pthread_create(&tid1, NULL, thread_routine1, &locks);
	printf("Main: Creation du premier thread [%ld]\n", tid1);
	pthread_create(&tid2, NULL, thread_routine2, &locks);
	printf("Main: Creation du second thread [%ld]\n", tid2);
	pthread_join(tid1, NULL);
	printf("Main: Union du premier thread [%ld]\n", tid1);
	pthread_join(tid2, NULL);
	printf("Main: Union du second thread [%ld]\n", tid2);
	if (locks.count == 2)
		printf("%sMain: OK: Le compte est %d\n", GREEN, locks.count);
	else
		printf("%sMain: ERREUR: Le compte est%u\n", RED, locks.count);
	pthread_mutex_destroy(&locks.lock_1);
	pthread_mutex_destroy(&locks.lock_2);
	return (0);
}*/
