/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/23 13:50:11 by kdelport          #+#    #+#             */
/*   Updated: 2021/11/12 08:46:41 by kdelport         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/philosophers.h"

void	free_elems(t_data *datas)
{
	sem_unlink("fork");
	sem_unlink("message");
	free(datas->philo);
}
