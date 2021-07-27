/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/23 13:50:32 by kdelport          #+#    #+#             */
/*   Updated: 2021/07/23 13:50:33 by kdelport         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	parsing(char **argv, t_data *datas)
{
	int ret;

	ret = ft_atoi(argv[1]);
	if (ret == -1)
		return (0);
	datas->philos_nb = ret;
	ret = ft_atoi(argv[2]);
	if (ret == -1)
		return (0);
	datas->t_to_die = ret;
	ret = ft_atoi(argv[3]);
	if (ret == -1)
		return (0);
	datas->t_to_eat = ret;
	ret = ft_atoi(argv[4]);
	if (ret == -1)
		return (0);
	datas->t_to_sleep = ret;
	if (!argv[5])
		return (1);
	ret = ft_atoi(argv[5]);
	if (ret == -1)
		return (0);
	datas->nb_must_eat = ret;
	return (1);
}
