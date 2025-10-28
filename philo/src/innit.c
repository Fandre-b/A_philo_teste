/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   innit.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gufreire <gufreire@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 17:52:01 by gufreire          #+#    #+#             */
/*   Updated: 2025/10/27 18:00:16 by gufreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philos.h"

bool	innit_threads(void)
{
	int		i;

	i = 0;
	while (i < args()->nb_philo)
	{
		if (pthread_create(args()->threads + i, NULL,
				&start, args()->philos + i))
			return (false);
		i++;
	}
	return (true);
}

t_philo	innit_philos(int i)
{
	t_philo		philo;

	philo.id = i;
	philo.n_meals = 0;
	philo.last_meal = time_now();
	return (philo);
}

bool	innit_mutexes(void)
{
	int		i;

	i = 0;
	while (i < args()->nb_philo)
	{
		args()->philos[i] = innit_philos(i);
		pthread_mutex_init(&args()->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&args()->prio, NULL);
	pthread_mutex_init(&args()->god, NULL);
	return (true);
}

bool	innit_structs(void)
{
	int		i;

	args()->threads = (pthread_t *)malloc((args()->nb_philo) * 8);
	if (!args()->threads)
		return (false);
	args()->forks = (pthread_mutex_t *)malloc((args()->nb_philo) * 40);
	if (!args()->forks)
	{
		free(args()->threads);
		args()->threads = NULL;
		return (false);
	}
	args()->philos = (t_philo *)malloc((args()->nb_philo) * sizeof(t_philo));
	if (!args()->philos)
	{
		free(args()->threads);
		args()->threads = NULL;
		free(args()->forks);
		args()->forks = NULL;
		return (false);
	}
	return (true);
}

bool	innit_everything(void)
{
	if (!innit_structs())
		return (false);
	args()->s_time = get_time();
	if (!innit_mutexes())
	{
		return (false);
	}
	if (!innit_threads())
	{
		return (false);
	}
	return (true);
}
