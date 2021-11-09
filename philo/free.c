/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/23 13:50:11 by kdelport          #+#    #+#             */
/*   Updated: 2021/11/09 08:52:36 by kdelport         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/philosophers.h"

void	destroy_mutex(t_data *datas)
{
	int		i;
	int		ret;

	i = 0;
	ret = 0;
	while (i < datas->philos_nb)
	{
		if ((ret = pthread_mutex_destroy(&datas->fork[i])) != 0)
			printf("Error with mutex destroy\n");	
		i++;
	}
	if (pthread_mutex_destroy(&datas->message) != 0)
		printf("Error with mutex destroy\n");
}

void	free_elems(t_data *datas)
{
	destroy_mutex(datas);
	free(datas->fork);
	free(datas->philo);
}
