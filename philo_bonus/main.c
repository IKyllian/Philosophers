/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/23 13:50:25 by kdelport          #+#    #+#             */
/*   Updated: 2021/11/15 11:30:32 by kdelport         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/philosophers.h"

void	*philo_routine(t_philo	*philo)
{
	uint64_t	time;

	if (philo->id % 2)
	{
		time = get_time(philo->datas->start_time) + philo->datas->t_to_sleep;
		while (!philo->datas->is_dead
			&& get_time(philo->datas->start_time) < time)
			usleep(100);
	}
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

void	*check_death(void *param)
{		
	t_philo	*philo;

	philo = (t_philo *)param;
	while (1)
	{
		if (get_time(philo->last_eat) > (uint64_t)philo->datas->t_to_die)
		{
			if (philo_action(philo, " died") != 0)
				exit(0);
			philo->datas->is_dead = 1;
			exit(0);
		}
		if (philo->datas->nb_must_eat != -1)
		{
			if (philo->eat_counter == philo->datas->nb_must_eat)
				exit(1);
		}
		usleep(50);
	}
	exit(2);
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
