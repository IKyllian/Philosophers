#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_philo
{
	int				id;
	int				last_eat;
	int				eat_counter;
	int				right_fork;
	int				left_fork;
	uint64_t		death_limit;
	pthread_t		thread_philo;
	struct s_data	*datas;
}				t_philo;

typedef struct s_data
{
	t_philo			*philo;
	int				philos_nb;
	uint64_t		start_time;
	uint64_t		t_to_eat;
	uint64_t		t_to_sleep;
	uint64_t		t_to_die;
	int				nb_must_eat;
	pthread_mutex_t	*fork;
	int				is_dead;
	pthread_mutex_t	message;
	struct timeval	tv;
}				t_data;

/*			Init			*/
int			init_tabs(t_data *datas);
int			init_struct(t_data *datas);
t_philo		init_struct_philo(int id, t_data *datas);
int			create_philo_thread(t_data *datas);
void		*philo_routine(void *param);

/*			Parsing			*/
int			ft_atoi(const char *nptr);
int			parsing(char **argv, t_data *datas);

/*			Utils			*/
uint64_t	get_time(t_data *datas);
int			philo_action(t_philo *philo, char *action);
int			get_index(t_philo *philo);

/*			Actions			*/
int			philo_eat(t_philo *philo);
int			take_forks(t_philo *philo);
int			clean_forks(t_philo *philo);

/*			Free / Error			*/
void		free_elems(t_data *datas);

#endif