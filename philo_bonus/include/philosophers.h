/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 09:34:47 by kdelport          #+#    #+#             */
/*   Updated: 2021/11/15 11:33:49 by kdelport         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <semaphore.h>
# include <errno.h>
# include <signal.h>
# include <string.h>

typedef struct s_philo
{
	int				id;
	struct timeval	last_eat;
	int				eat_counter;
	pthread_t		thread_philo;
	pid_t			pid;
	struct s_data	*datas;
}				t_philo;

typedef struct s_data
{
	t_philo			*philo;
	int				philos_nb;
	struct timeval	start_time;
	uint64_t		t_to_eat;
	uint64_t		t_to_sleep;
	uint64_t		t_to_die;
	int				nb_must_eat;
	sem_t			*fork;
	int				is_dead;
	sem_t			*message;
}				t_data;

/*			Init			*/
int			init_tabs(t_data *datas);
int			init_struct(t_data *datas);
t_philo		init_struct_philo(int id, t_data *datas);
int			create_philo_thread(t_data *datas);
void		*philo_routine(t_philo	*philo);
char		*get_name(char *name);

/*			Parsing			*/
int			ft_atoi(const char *nptr);
int			parsing(char **argv, t_data *datas);

/*			Utils			*/
uint64_t	get_time(struct timeval timeval);
int			philo_action(t_philo *philo, char *action);
int			get_index(t_philo *philo);
void		*check_death(void *param);
int			wait_function(t_data *datas);

/*			Actions			*/
int			philo_eat(t_philo *philo);
int			take_forks(t_philo *philo);
int			clean_forks(t_philo *philo);

/*			Free / Error			*/
void		free_elems(t_data *datas);

#endif