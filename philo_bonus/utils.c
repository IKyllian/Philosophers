/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/23 13:48:41 by kdelport          #+#    #+#             */
/*   Updated: 2021/07/27 15:17:35 by kdelport         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_atoi(const char *nptr)
{
	int		i;
	long	nbr;

	i = 0;
	nbr = 0;
	if (!nptr)
		return (-1);
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	while (nptr[i])
	{
		if (nptr[i] >= 48 && nptr[i] <= 57)
			nbr = nbr * 10 + (nptr[i++] - 48);
		else
			return (-1);
	}
	return (nbr);
}

void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		write(1, &str[i++], 1);
}

void	ft_putnbr(uint64_t nb)
{
	char	c;
	if (nb >= 10)
	{
		ft_putnbr(nb / 10);
		ft_putnbr(nb % 10);
	}
	else
	{
		c = nb + 48;
		write(1, &c, 1);
	}	
}

uint64_t	get_time(t_data *datas)
{
	uint64_t	ms;

	gettimeofday(&datas->tv, NULL);
	ms = (datas->tv.tv_sec) * 1000 + (datas->tv.tv_usec) / 1000;
	return (ms);
}

int	philo_action(t_philo *philo, char *action)
{
	sem_wait(philo->datas->message);
	if (!philo->datas->is_dead)
	{
		ft_putnbr(get_time(philo->datas) - philo->datas->start_time);
		ft_putstr("\t");
		ft_putnbr((uint64_t)philo->id);
		ft_putstr(action);
		ft_putstr("\n");
	}
	sem_post(philo->datas->message);
	return (0);
}


