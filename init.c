#include "philosophers.h"

t_philo	init_struct_philo(int id, t_data *datas)
{
	t_philo philo;

	philo.id = id;
	philo.is_eating = 0;
	philo.is_sleeping = 0;
	philo.start_eating = 0;
	philo.start_sleeping = 0;
	philo.eat_counter = 0;
	philo.last_eat = 0;
	philo.timer = 0;
	philo.is_dead = 0;
	philo.datas = datas;
	return (philo);
}

t_data	init_struct(void)
{
	t_data datas;

	datas.philo = NULL;
	datas.t_to_die = 0;
	datas.t_to_eat = 0;
	datas.t_to_sleep = 0;
	datas.philos_nb = 0;
	datas.nb_must_eat = -1;	
	return (datas);
}

int	init_tabs(t_data *datas)
{
	int	i;

	i = 0;
	datas->philo = malloc(sizeof(t_philo) * datas->philos_nb);
	if (!datas->philo)
	{
		printf("Error: Alloc memory\n");
		return (1);
	}
	datas->fork = malloc(sizeof(pthread_mutex_t) * datas->philos_nb);
	if (!datas->philo)
	{
		printf("Error: Alloc memory\n");
		return (1);
	}
	while (i < datas->philos_nb)
	{
		datas->philo[i] = init_struct_philo(i + 1, datas);
		i++;
	}
	return (0);
}