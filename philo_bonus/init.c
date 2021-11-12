/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/23 13:50:20 by kdelport          #+#    #+#             */
/*   Updated: 2021/11/12 09:27:00 by kdelport         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/philosophers.h"

t_philo	init_struct_philo(int id, t_data *datas)
{
	t_philo	philo;

	philo.id = id;
	philo.eat_counter = 0;
	philo.left_fork = id - 1;
	if (id >= datas->philos_nb)
		philo.right_fork = 0;
	else
		philo.right_fork = id;
	philo.datas = datas;
	return (philo);
}

int	init_struct(t_data *datas)
{
	t_data	new;

	new.philo = NULL;
	new.t_to_die = 0;
	new.t_to_eat = 0;
	new.t_to_sleep = 0;
	new.philos_nb = 0;
	new.is_dead = 0;
	new.nb_must_eat = -1;
	sem_unlink("message");
	new.message = sem_open("message", O_CREAT, S_IRWXU, 1);
	*datas = new;
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
	while (i < datas->philos_nb)
	{
		datas->philo[i] = init_struct_philo(i + 1, datas);
		i++;
	}
	return (0);
}

int	create_philo_thread(t_data *datas)
{
	int	i;

	i = 0;
	while (++i < datas->philos_nb)
	{
		datas->philo[i].last_eat = datas->start_time;
		datas->philo[i].pid = fork();
		if (datas->philo[i].pid == 0)
		{
			if (pthread_create(&datas->philo[i].thread_philo, \
				NULL, philo_routine, (void *)&datas->philo[i]) != 0)
			{
				printf("Error with the thread creation\n");
				exit(5);
			}
			exit_child(datas, i);
		}
		i++;
	}
	return (wait_function(datas));
}
