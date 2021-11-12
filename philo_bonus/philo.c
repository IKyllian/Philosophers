/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 09:17:46 by kdelport          #+#    #+#             */
/*   Updated: 2021/11/12 15:43:47 by kdelport         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/philosophers.h"

void	kill_children(t_data *datas)
{
	int	j;

	j = 0;
	while (j < datas->philos_nb)
		kill(datas->philo[j++].pid, SIGKILL);
}

int	wait_function(t_data *datas)
{
	int	status;
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (i < datas->philos_nb)
	{
		waitpid(-1, &status, 0);
		if (WEXITSTATUS(status) == 0 || WEXITSTATUS(status) == 5)
		{
			kill_children(datas);
			return (1);
		}
		else if (WEXITSTATUS(status) == 1)
		{
			count++;
			if (count == datas->philos_nb)
				printf("Each philosophers ate %i times\n", datas->nb_must_eat);
		}
		i++;
	}
	while (wait(NULL) != -1)
		continue ;
	return (0);
}

void	exit_child(t_data *datas, int i)
{
	// int	ret;

	while (1)
	{
		philo_routine(&datas->philo[i]);
		// if (ret != 2)
		// 	exit(ret);
	}
}
