/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/23 13:49:54 by kdelport          #+#    #+#             */
/*   Updated: 2021/11/12 09:25:41 by kdelport         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/philosophers.h"

int	philo_eat(t_philo *philo)
{
	uint64_t	time;

	gettimeofday(&philo->last_eat, NULL);
	if (philo_action(philo, " is eating") != 0)
		return (1);
	time = get_time(philo->datas->start_time) + philo->datas->t_to_eat;
	while (get_time(philo->datas->start_time) < time)
		usleep(100);
	philo->eat_counter++;
	return (0);
}

int	take_forks(t_philo *philo)
{
	if (sem_wait(philo->datas->fork) != 0)
		return (1);
	if (philo_action(philo, " has taken a fork") != 0)
		return (1);
	if (sem_wait(philo->datas->fork) != 0)
		return (1);
	if (philo_action(philo, " has taken a fork") != 0)
		return (1);
	return (0);
}

int	clean_forks(t_philo *philo)
{
	uint64_t	time;

	if (philo_action(philo, " is sleeping") != 0)
		return (1);
	if (sem_post(philo->datas->fork) != 0)
		return (1);
	if (sem_post(philo->datas->fork) != 0)
		return (1);
	time = get_time(philo->datas->start_time) + philo->datas->t_to_sleep;
	while (get_time(philo->datas->start_time) < time)
		usleep(100);
	if (philo_action(philo, " is thinking") != 0)
		return (1);
	return (0);
}
