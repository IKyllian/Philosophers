/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/23 13:50:25 by kdelport          #+#    #+#             */
/*   Updated: 2021/07/23 13:50:25 by kdelport         ###   ########.fr       */
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
	while (1)
	{
		if (philo->datas->nb_must_eat > -1
			|| (philo->datas->nb_must_eat > -1
			&& philo->eat_counter < philo->datas->nb_must_eat))
		{
			take_forks(philo);
			if (philo_eat(philo))
				return (NULL);
			clean_forks(philo);
			philo_action(philo, " is thinking");
		}
	}
	return (NULL);
}

int		philo_is_dead(t_data *datas, int i)
{
	if (datas->philo[i].last_eat != (uint64_t)-1 && ((get_time(datas) - \
		datas->start_time) - datas->philo[i].last_eat) >= datas->t_to_die)
	{
		philo_action(&datas->philo[i], " died");
		datas->is_dead = 1;
		return (1);
	}
	return (0);
}

void	check_death(t_data *datas)
{
	int	i;
	int	exit;

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
		printf("Each philosophers ate %i times\n", datas->nb_must_eat);
}

int	main(int argc, char **argv)
{
	t_data	datas;

	if (argc >= 5 && argc <= 6)
	{
		if (init_struct(&datas) != 0)
			return (1);
		if (parsing(argv, &datas))
		{
			if (init_tabs(&datas))
				return (1);
			if (create_philo_thread(&datas))
				return (1);
			check_death(&datas);
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