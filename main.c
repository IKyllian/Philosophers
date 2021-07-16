#include "philosophers.h"

int	philo_eat(t_philo *philo)
{
	int	max;

	max = get_index(philo);
	if (philo->last_eat != (uint64_t)-1 && ((get_time(philo->datas) - \
		philo->datas->start_time) - philo->last_eat) >= philo->datas->t_to_die)
	{
		philo->is_dead = 1;
		return (1);
	}
	if (pthread_mutex_lock(&philo->datas->fork[philo->id - 1]) != 0)
		return (1);
	if (pthread_mutex_lock(&philo->datas->fork[max]) != 0)
		return (1);
	philo_action(philo, "eating");
	philo->is_eating = 1;
	philo->start_eating = get_time(philo->datas) - philo->datas->start_time;
	philo->eat_counter++;
	if (usleep(philo->datas->t_to_eat * 1000) == -1)
		return (1);
	if (pthread_mutex_unlock(&philo->datas->fork[philo->id - 1]) != 0)
		return (1);
	if (pthread_mutex_unlock(&philo->datas->fork[max]) != 0)
		return (1);
	return (0);
}

int	set_philo_status(t_philo *philo)
{
	if (!philo->is_eating && !philo->is_sleeping)
	{
		philo_eat(philo);
	}
	else if (philo->is_eating)
	{
		philo_action(philo, "sleeping");
		philo->is_eating = 0;
		philo->is_sleeping = 1;
		philo->last_eat = get_time(philo->datas) - philo->datas->start_time;
		philo->start_sleeping = get_time(philo->datas) - philo->datas->start_time;
		if (usleep(philo->datas->t_to_sleep * 1000) == -1)
			return (1);
		if (philo->last_eat != (uint64_t)-1 && ((get_time(philo->datas) - philo->datas->start_time) - philo->last_eat) >= philo->datas->t_to_die)
		{
			philo->is_dead = 1;
			return (1);
		}
		philo_action(philo, "thinking");
		philo->is_sleeping = 0;
	}
	return (0);
}

void	*philo_routine(void *param)
{
	int i;
	t_philo *philo;

	philo = (t_philo *)param;
	i = 0;
	while (!philo->is_dead || (!philo->is_dead
		&& (philo->datas->nb_must_eat > 0
		&& philo->eat_counter < philo->datas->nb_must_eat)))
	{
		set_philo_status(philo);
	}
	printf("%lli Philo %i died\n", get_time(philo->datas) - philo->datas->start_time, philo->id);
	return (NULL);
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
	i = 0;
	while (i < datas->philos_nb)
	{
		pthread_mutex_destroy(&datas->fork[i]);
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