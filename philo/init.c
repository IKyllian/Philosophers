/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/23 13:50:20 by kdelport          #+#    #+#             */
/*   Updated: 2021/11/04 13:21:43 by kdelport         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_philo	init_struct_philo(int id, t_data *datas)
{
	t_philo philo;

	philo.id = id;
	philo.eat_counter = 0;
	philo.left_fork = id - 1;
	if (id >= datas->philos_nb)
		philo.right_fork = 0;
	else
		philo.right_fork = id;
	philo.last_eat = -1;
	philo.datas = datas;
	return (philo);
}

int	init_struct(t_data *datas)
{
	t_data new;

	new.philo = NULL;
	new.t_to_die = 0;
	new.t_to_eat = 0;
	new.t_to_sleep = 0;
	new.philos_nb = 0;
	new.is_dead = 0;
	new.nb_must_eat = -1;
	if (pthread_mutex_init(&new.message, NULL) != 0)
	{
		printf("Error with mutex init");
		return (1);
	}
	*datas = new;
	return (0);
}

int	init_forks_mutex(t_data *datas)
{
	int	i;

	i = 0;
	while (i < datas->philos_nb)
	{
		if (pthread_mutex_init(&datas->fork[i], NULL) != 0)
		{
			printf("Error with mutex init");
			return (1);
		}	
		i++;
	}
	return (0);
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
	if (!datas->fork)
	{
		printf("Error: Alloc memory\n");
		free(datas->philo);
		return (1);
	}
	while (i < datas->philos_nb)
	{
		datas->philo[i] = init_struct_philo(i + 1, datas);
		i++;
	}
	if (init_forks_mutex(datas) != 0)
		return (1);
	return (0);
}

int	create_philo_thread(t_data *datas)
{
	long	i;

	i = 0;
	datas->start_time = get_time(datas);
	while (i < datas->philos_nb)
	{
		datas->philo[i].death_limit = get_time(datas) + datas->t_to_die;
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