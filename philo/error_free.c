/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/23 13:50:11 by kdelport          #+#    #+#             */
/*   Updated: 2021/11/04 12:11:56 by kdelport         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	destroy_mutex(t_data *datas)
{
	int		i;
	int		ret;

	i = 0;
	ret = 0;
	while (i < datas->philos_nb)
	{
		pthread_mutex_destroy(&datas->fork[i]);
		// pthread_mutex_unlock(&datas->fork[i]);
		// if ((ret = pthread_mutex_destroy(&datas->fork[i])) != 0)
		// 	printf("Error with mutex destroy | ret = %i | i = %i\n", ret, i);	
		i++;
	}
	// if (pthread_mutex_destroy(&datas->message) != 0)
	// 	printf("Error with mutex destroy\n");
	pthread_mutex_destroy(&datas->message);
}

void	free_elems(t_data *datas)
{
	destroy_mutex(datas);
	free(datas->fork);
	free(datas->philo);
}