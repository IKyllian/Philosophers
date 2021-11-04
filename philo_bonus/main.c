/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/23 13:50:25 by kdelport          #+#    #+#             */
/*   Updated: 2021/08/11 18:52:33 by kdelport         ###   ########.fr       */
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
		usleep(10000);
	while ((!philo->datas->is_dead && philo->datas->nb_must_eat == -1)
		|| (!philo->datas->is_dead && philo->datas->nb_must_eat != -1
		&& philo->eat_counter < philo->datas->nb_must_eat))
	{
		take_forks(philo);
		if (philo_eat(philo))
			return (NULL);
		if (clean_forks(philo) == 1)
			return (NULL);
		if (philo_action(philo, " is thinking") != 0)
			return (NULL);
	}
	return (NULL);
}

int		philo_is_dead(t_data *datas, int i)
{
	if (datas->philo[i].last_eat != (uint64_t)-1
		&& datas->philo[i].death_limit < get_time(datas))
	{
		if (philo_action(&datas->philo[i], " died") != 0)
			return (1);
		datas->is_dead = 1;
		return (1);
	}
	return (0);
}

int	check_death(t_data *datas)
{
	int	i;
	int	exit;

	exit = 0;
	while ((!datas->is_dead && datas->nb_must_eat == -1)
		|| (!datas->is_dead && datas->nb_must_eat != -1
		&& exit != datas->philos_nb))
	{
		i = 0;
		exit = 0;
		while (i < datas->philos_nb)
		{
			if (philo_is_dead(datas, i))
				break ;
			if (datas->nb_must_eat != -1)
			{
				if (datas->philo[i].eat_counter == datas->nb_must_eat)
					exit++;
			}
			i++;
			usleep(100);
		}
	}
	if (datas->nb_must_eat != -1 && exit == datas->philos_nb)
	{
		printf("Each philosophers ate %i times\n", datas->nb_must_eat);
		return (exit);
	}	
	return (0);
}

// int	join_philo(t_data *datas)
// {
// 	int		i;
// 	void	*ret;
	
// 	i = 0;
// 	while (i < datas->philos_nb)
// 	{
// 		ret = NULL;
// 		if (pthread_join(datas->philo[i].thread_philo, ret) != 0)
// 		{
// 			printf("Error with join | i = %i\n", i);
// 			return (1);
// 		}	
// 		i++;
// 	}
// 	return (0);
// }

int	main(int argc, char **argv)
{
	t_data	datas;
	// int		ret;

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
			if (create_philo_thread(&datas))
				return (1);
			check_death(&datas);
			// ret = check_death(&datas);
			// join_philo(&datas);
			// if (ret == datas.philos_nb)
				// printf("Each philosophers ate %i times\n", datas.nb_must_eat);
			free_elems(&datas);
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