/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/23 13:50:11 by kdelport          #+#    #+#             */
/*   Updated: 2021/11/12 09:40:45 by kdelport         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/philosophers.h"

void	destroy_mutex(t_data *datas)
{
	int		i;

	i = 0;
	while (i < datas->philos_nb)
	{
		if (pthread_mutex_destroy(&datas->fork[i]) != 0)
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
