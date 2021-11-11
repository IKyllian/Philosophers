/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/23 13:50:25 by kdelport          #+#    #+#             */
/*   Updated: 2021/11/11 12:25:53 by kdelport         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*philo_routine(void *param)
{
	int i;
	t_philo *philo;

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

// int		philo_is_dead(t_data *datas, int i)
// {
// 	if (get_time(datas->philo[i].last_eat) > (uint64_t)datas->t_to_die)
// 	{
// 		if (philo_action(&datas->philo[i], " died") != 0)
// 			return (1);
// 		datas->is_dead = 1;
// 		return (1);
// 	}
// 	return (0);
// }

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
		{
			printf("Each philosophers ate %i times\n", philo->datas->nb_must_eat);
			return (1);
		}
	}
	return (2);
}

void	end_of_prog(t_data *datas)
{
	while (datas->philos_nb--)
		pthread_join(datas->philo[datas->philos_nb].thread_philo, NULL);
	free_elems(datas);
}

int	main(int argc, char **argv)
{
	t_data	datas;

	if (argc >= 5 && argc <= 6)
	{
		if (init_struct(&datas) != 0)
			return (1);
		if (parsing(argv, &datas) && datas.philos_nb >= 2)
		{
			sem_unlink("fork");
			datas.fork = sem_open("fork", O_CREAT, S_IRWXU, datas.philos_nb);
			if (init_tabs(&datas))
				return (1);
			gettimeofday(&datas.start_time, NULL);
			if (create_philo_thread(&datas))
				return (1);
			end_of_prog(&datas);
			return (0);
		}
		else
			printf("Error: Arguments should be positives numbers and it must have 2 or more philos\n");
		return (1);
	}
	else
		printf("Error: Arguments\n");
	return (1);
}