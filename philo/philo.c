/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 14:23:10 by kdelport          #+#    #+#             */
/*   Updated: 2021/11/12 14:24:28 by kdelport         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/philosophers.h"

void	select_philo(t_philo *philo)
{
	uint64_t	time;

	if (philo->id % 2)
	{
		time = get_time(philo->datas->start_time) + philo->datas->t_to_sleep;
		while (!philo->datas->is_dead
			&& get_time(philo->datas->start_time) < time)
			usleep(100);
	}
}

void	*philo_routine(void *param)
{
	int		i;
	t_philo	*philo;

	philo = (t_philo *)param;
	i = 0;
	while (!philo->datas->sync)
		usleep(5);
	philo->last_eat = philo->datas->start_time;
	philo->datas->count++;
	select_philo(philo);
	while ((!philo->datas->is_dead && philo->datas->nb_must_eat == -1)
		|| (!philo->datas->is_dead && philo->datas->nb_must_eat != -1 \
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

int	philo_is_dead(t_data *datas, int i)
{
	if (get_time(datas->philo[i].last_eat) > (uint64_t)datas->t_to_die)
	{
		if (philo_action(&datas->philo[i], " died") != 0)
			return (1);
		datas->is_dead = 1;
		if (pthread_mutex_unlock(&datas->fork[datas->philo[i].left_fork]) != 0)
			return (1);
		if (pthread_mutex_unlock(&datas->fork[datas->philo[i].right_fork]) != 0)
			return (1);
		return (1);
	}
	return (0);
}

void	check_death(t_data *datas)
{
	int	i;
	int	exit;

	exit = 0;
	while ((!datas->is_dead && datas->nb_must_eat == -1)
		|| (!datas->is_dead && datas->nb_must_eat != -1 \
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
