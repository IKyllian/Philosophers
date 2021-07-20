#include "philosophers.h"

void	kill_philos(t_data *datas)
{
	int	i;

	i = 0;
	while (i < datas->philos_nb)
	{
		pthread_detach(datas->philo[i].thread_philo);
		i++;
	}
}

int	philo_eat(t_philo *philo)
{
	if (philo->last_eat != (uint64_t)-1 && ((get_time(philo->datas) - \
		philo->datas->start_time) - philo->last_eat) >= philo->datas->t_to_die)
	{
		philo_action(philo, "died");
		philo->datas->is_dead = 1;
		return (1);
	}
	philo_action(philo, "eating");
	philo->last_eat = get_time(philo->datas) - philo->datas->start_time;
	if (usleep(philo->datas->t_to_eat * 1000) == -1)
		return (1);
	philo->eat_counter++;
	
	return (0);
}

int	take_forks(t_philo *philo)
{
	if (pthread_mutex_lock(&philo->datas->fork[philo->left_fork]) != 0)
		return (1);
	// philo_action(philo, "has taken a fork");	
	if (pthread_mutex_lock(&philo->datas->fork[philo->right_fork]) != 0)
		return (1);
	// philo_action(philo, "has taken a fork");
	return (0);
}

int	clean_forks(t_philo *philo)
{
	philo_action(philo, "sleeping");
	if (pthread_mutex_unlock(&philo->datas->fork[philo->left_fork]) != 0)
		return (1);
	if (pthread_mutex_unlock(&philo->datas->fork[philo->right_fork]) != 0)
		return (1);
	if (usleep(philo->datas->t_to_sleep * 1000) == -1)
		return (1);
	return (0);
}

void	*philo_routine(void *param)
{
	int i;
	t_philo *philo;

	philo = (t_philo *)param;
	i = 0;
	while (!philo->datas->is_dead || (!philo->datas->is_dead
		&& (philo->datas->nb_must_eat > 0
		&& philo->eat_counter < philo->datas->nb_must_eat)))
	{
		take_forks(philo);
		if (philo_eat(philo))
			return (NULL);
		clean_forks(philo);
		philo_action(philo, "thinking");
	}
	// printf("%lli Philo %i died\n", get_time(philo->datas) - philo->datas->start_time, philo->id);
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
	// i = 0;
	// while (i < datas->philos_nb)
	// {
	// 	pthread_mutex_destroy(&datas->fork[i]);
	// 	i++;
	// }
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
			kill_philos(&datas);
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