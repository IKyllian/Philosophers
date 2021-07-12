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