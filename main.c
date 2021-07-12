#include "philosophers.h"

uint64_t	get_time(t_data *datas)
{
	uint64_t ms;

	gettimeofday(&datas->tv, NULL);
	ms = (datas->tv.tv_sec) * 1000 + (datas->tv.tv_usec) / 1000;
	return (ms);
}

void	philo_eating(t_philo *philo)
{
	printf("%llu %i is eating\n", get_time(philo->datas) - philo->datas->start_time, philo->id);
	// philo->timer++;
}

void	philo_sleeping(t_philo *philo)
{
	printf("%llu %i is sleeping\n", get_time(philo->datas) - philo->datas->start_time, philo->id);
	// philo->timer++;
}

void	philo_thinking(t_philo *philo)
{
	printf("%llu %i is thinking\n", get_time(philo->datas) - philo->datas->start_time, philo->id);
	
}

void	set_philo_status(t_philo *philo)
{
	if (!philo->is_eating && !philo->is_sleeping)
	{
		philo_eating(philo);
		philo->is_eating = 1;
		philo->start_eating = get_time(philo->datas) - philo->datas->start_time;
		usleep(philo->datas->t_to_eat * 1000);
		philo->eat_counter++;
	}
	else if (philo->is_eating)
	{
		philo_sleeping(philo);
		philo->is_eating = 0;
		philo->is_sleeping = 1;
		philo->last_eat = get_time(philo->datas) - philo->datas->start_time;
		philo->start_sleeping = get_time(philo->datas) - philo->datas->start_time;
		usleep(philo->datas->t_to_sleep * 1000);
	}
	else if (philo->is_sleeping)
	{
		philo->is_eating = 0;
		philo->is_sleeping = 0;
		philo_thinking(philo);
	}
}

void	*philo_routine(void *param)
{
	int i;
	t_philo *philo;

	philo = (t_philo *)param;
	i = 0;
	// printf("T to eat = %lli | T to sleep = %lli\n", philo->datas->t_to_eat, philo->datas->t_to_sleep);
	while (!philo->is_dead && (philo->datas->nb_must_eat > 0 && philo->eat_counter < philo->datas->nb_must_eat))
	{
		set_philo_status(philo);
	}
	printf("Philo %i died\n", philo->id);
	return (NULL);
}

int	create_philo_thread(t_data *datas)
{
	long	i;

	i = 0;
	datas->start_time = get_time(datas);
	while (i < datas->philos_nb)
	{
		if (pthread_create(&datas->philo[i].thread_philo, NULL, philo_routine,
			(void *)&datas->philo[i]) != 0)
		{
			printf("Error with the thread creation\n");
			return (1);
		}
		i++;
	}
	return (0);
}

int	philo_thread_join(t_data *datas)
{
	int		i;
	void	*ret;

	i = 0;
	while (i < datas->philos_nb)
	{
		ret = NULL;
		if (pthread_join(datas->philo[i].thread_philo, ret) != 0)
		{
			printf("Error with pthread_join function\n");
			return (1);
		}
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data		datas;

	if (argc >= 5 && argc <= 6)
	{
		datas = init_struct();
		if (parsing(argv, &datas))
		{
			if (init_tabs(&datas))
				return (1);
			if (create_philo_thread(&datas))
				return (1);
			if (philo_thread_join(&datas))
				return (1);
			return (0);
		}
		else
			printf("Error: Arguments should be positives numbers\n");
		return (1);
	}
	else
		printf("Error: Arguments\n");
	return (1);
}