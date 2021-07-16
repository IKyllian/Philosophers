#include "philosophers.h"

uint64_t	get_time(t_data *datas)
{
	uint64_t ms;

	gettimeofday(&datas->tv, NULL);
	ms = (datas->tv.tv_sec) * 1000 + (datas->tv.tv_usec) / 1000;
	return (ms);
}

void	philo_action(t_philo *philo, char *action)
{
	printf("%llu %i is %s\n", get_time(philo->datas) - philo->datas->start_time, philo->id, action);
}

int	get_index(t_philo *philo)
{
	int	index;

	if (philo->id >= philo->datas->philos_nb)
		index = 0;
	else
		index = philo->id;
	return (index);
}
