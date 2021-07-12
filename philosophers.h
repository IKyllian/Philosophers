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
	uint64_t		timer;
	uint64_t		last_eat;
	int				is_eating;
	int				is_sleeping;
	int				eat_counter;
	uint64_t		start_eating;
	uint64_t		start_sleeping;
	pthread_t		thread_philo;
	int				is_dead;
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
	struct timeval	tv;
}				t_data;

/*			Parsing			*/
int		ft_atoi(const char *nptr);
int		parsing(char **argv, t_data *datas);

/*			Init			*/
int		init_tabs(t_data *datas);
t_data	init_struct(void);
t_philo	init_struct_philo(int id, t_data *datas);

#endif