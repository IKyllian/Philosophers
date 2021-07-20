#include "philosophers.h"

int		ft_atoi(const char *nptr)
{
	int		i;
	long	nbr;

	i = 0;
	nbr = 0;
	if (!nptr)
		return (-1);
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	while (nptr[i])
	{
		if (nptr[i] >= 48 && nptr[i] <= 57)
			nbr = nbr * 10 + (nptr[i++] - 48);
		else
			return (-1);
	}
	return (nbr);
}

void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		write(1, &str[i++], 1);
}

void	ft_putnbr(uint64_t n)
{
	char	str[13];
	int		length;

	if (n == 0)
		str[0] = '0';
	length = 0;
	while (n != 0)
	{
		str[length++] = '0' + (n % 10);
		n = (n / 10);
	}
	if (length > 0)
		length--;
	while (length >= 0)
		write(1, &str[length--], 1);
}

uint64_t	get_time(t_data *datas)
{
	uint64_t ms;

	gettimeofday(&datas->tv, NULL);
	ms = (datas->tv.tv_sec) * 1000 + (datas->tv.tv_usec) / 1000;
	return (ms);
}

void	philo_action(t_philo *philo, char *action)
{
	pthread_mutex_lock(&philo->datas->message);
	if (!philo->datas->is_dead)
	{
		ft_putnbr(get_time(philo->datas) - philo->datas->start_time);
		ft_putstr("\t");
		ft_putnbr((uint64_t)philo->id);
		ft_putstr(" is ");
		ft_putstr(action);
		ft_putstr("\n");
	}
	pthread_mutex_unlock(&philo->datas->message);
}


