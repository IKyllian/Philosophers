/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/23 13:49:54 by kdelport          #+#    #+#             */
/*   Updated: 2021/07/27 15:16:09 by kdelport         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	philo_eat(t_philo *philo)
{
	if (philo_action(philo, " is eating") != 0)
		return (1);
	philo->last_eat = get_time(philo->datas) - philo->datas->start_time;
	if (usleep(philo->datas->t_to_eat * 1000) == -1)
		return (1);
	philo->eat_counter++;
	return (0);
}

int	take_forks(t_philo *philo)
{
	if (pthread_mutex_lock(&philo->datas->fork[philo->left_fork]) != 0)
		return (1);
	if (philo_action(philo, " has taken a fork") != 0)
		return (1);	
	if (pthread_mutex_lock(&philo->datas->fork[philo->right_fork]) != 0)
		return (1);
	if (philo_action(philo, " has taken a fork") != 0)
		return (1);
	return (0);
}

int	clean_forks(t_philo *philo)
{
	if (philo_action(philo, " is sleeping") != 0)
		return (1);
	if (pthread_mutex_unlock(&philo->datas->fork[philo->left_fork]) != 0)
		return (1);
	if (pthread_mutex_unlock(&philo->datas->fork[philo->right_fork]) != 0)
		return (1);
	if (usleep(philo->datas->t_to_sleep * 1000) == -1)
		return (1);
	return (0);
}