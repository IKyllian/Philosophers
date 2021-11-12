/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/23 13:50:25 by kdelport          #+#    #+#             */
/*   Updated: 2021/11/12 09:28:05 by kdelport         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/philosophers.h"

void	*philo_routine(void *param)
{
	int		i;
	t_philo	*philo;

	philo = (t_philo *)param;
	i = 0;
	if (philo->id % 2)
		usleep(1000);
	while ((!philo->datas->is_dead && philo->datas->nb_must_eat == -1)
		|| (!philo->datas->is_dead && philo->datas->nb_must_eat != -1
			&& philo->eat_counter < philo->datas->nb_must_eat))
	{
		if (take_forks(philo) == 1)
			return (NULL);
		if (philo_eat(philo))
			return (NULL);
		if (clean_forks(philo) == 1)
			return (NULL);
	}
	return (NULL);
}

int	check_death(t_philo *philo)
{		
	if (get_time(philo->last_eat) > (uint64_t)philo->datas->t_to_die)
	{
		if (philo_action(philo, " died") != 0)
			return (0);
		philo->datas->is_dead = 1;
		return (0);
	}
	if (philo->datas->nb_must_eat != -1)
	{
		if (philo->eat_counter == philo->datas->nb_must_eat)
			return (1);
	}
	return (2);
}

int	main(int argc, char **argv)
{
	t_data	datas;

	if (argc >= 5 && argc <= 6)
	{
		if (init_struct(&datas) != 0)
			return (1);
		if (parsing(argv, &datas) && datas.philos_nb >= 1)
		{
			sem_unlink("fork");
			datas.fork = sem_open("fork", O_CREAT, S_IRWXU, datas.philos_nb);
			if (init_tabs(&datas))
				return (1);
			gettimeofday(&datas.start_time, NULL);
			if (create_philo_thread(&datas))
				return (1);
			free_elems(&datas);
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
