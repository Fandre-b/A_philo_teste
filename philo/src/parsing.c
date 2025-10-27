/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gufreire <gufreire@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 15:27:06 by gufreire          #+#    #+#             */
/*   Updated: 2025/10/27 18:10:56 by gufreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philos.h"

bool	args_pars(char **av)
{
	args()->nb_philo = atoi_args(av[1]);
	args()->time_to_d = atoi_args(av[2]);
	args()->time_to_e = atoi_args(av[3]);
	args()->time_to_s = atoi_args(av[4]);
	if (av[5])
	{
		args()->nb_times_e = atoi_args(av[5]);
		if (args()->nb_philo < 1 || args()->time_to_d < 1
			|| args()->time_to_e < 1
			|| args()->time_to_s < 1 || args()->nb_times_e < 1)
			return (true);
		return (false);
	}
	if (args()->nb_philo < 1 || args()->time_to_d < 1
		|| args()->time_to_e < 1 || args()->time_to_s < 1)
		return (true);
	else
		return (false);
}

int	atoi_args(char *nb)
{
	int		i;
	long	nbr;

	nbr = 0;
	i = 0;
	while (nb[i])
	{
		if (nb[i] >= '0' && nb[i] <= '9')
		{
			nbr = (nbr * 10) + (nb[i] - '0');
			if (nbr > INT_MAX || nbr < INT_MIN)
				return (-1);
		}
		else
			return (-1);
		i++;
	}
	return (nbr);
}

bool	pars(int ac, char **av)
{
	if (ac != 5 && ac != 6)
	{
		printf("Wrong number of arguments\n");
		return (false);
	}
	if (args_pars(av) == true)
	{
		printf("Wrong input values\n");
		return (false);
	}
	return (true);
}
