/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/23 13:50:11 by kdelport          #+#    #+#             */
/*   Updated: 2021/07/23 13:50:12 by kdelport         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	destroy_mutex(t_data *datas)
{
	int		i;

	i = 0;
	while (i < datas->philos_nb)
	{
		pthread_mutex_destroy(&datas->fork[i]);
		i++;
	}
	
	pthread_mutex_destroy(&datas->message);
}

void	free_elems(t_data *datas)
{
	destroy_mutex(datas);
	free(datas->fork);
	free(datas->philo);
}
