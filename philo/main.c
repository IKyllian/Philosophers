/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/23 13:50:25 by kdelport          #+#    #+#             */
/*   Updated: 2021/11/12 14:34:47 by kdelport         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/philosophers.h"

void	end_of_prog(t_data *datas)
{
	while (datas->philos_nb--)
		pthread_join(datas->philo[datas->philos_nb].thread_philo, NULL);
	free_elems(datas);
}

void	sync_main_prog(t_data *datas)
{
	gettimeofday(&datas->start_time, NULL);
	datas->sync = 1;
	while (datas->count < datas->philos_nb)
		continue ;
}

int	main(int argc, char **argv)
{
	t_data	datas;

	if (argc >= 5 && argc <= 6)
	{
		if (init_struct(&datas) != 0)
			return (1);
		if (parsing(argv, &datas) && datas.philos_nb >= 1)
		{
			if (init_tabs(&datas))
				return (1);
			if (create_philo_thread(&datas))
				return (1);
			sync_main_prog(&datas);
			check_death(&datas);
			end_of_prog(&datas);
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
