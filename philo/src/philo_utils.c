/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gufreire <gufreire@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 17:52:11 by gufreire          #+#    #+#             */
/*   Updated: 2025/10/27 18:22:44 by gufreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philos.h"

void	clean(void)
{
	int		i;

	i = 0;
	while (i < args()->nb_philo)
	{
		if (pthread_join(args()->threads[i], NULL))
			return ;
		i++;
	}
	i = 0;
	while (i < args()->nb_philo)
	{
		pthread_mutex_destroy(args()->forks + i);
		i++;
	}
	pthread_mutex_destroy(&args()->prio);
	pthread_mutex_destroy(&args()->god);
	free(args()->threads);
	args()->threads = NULL;
	free(args()->forks);
	args()->forks = NULL;
	free(args()->philos);
	args()->philos = NULL;
}

bool	check_stop(void)
{
	pthread_mutex_lock(&args()->god);
	if (args()->stop)
	{
		pthread_mutex_unlock(&args()->god);
		return (true);
	}
	pthread_mutex_unlock(&args()->god);
	return (false);
}

bool	check_death(void)
{
	long	timestamp;
	long	limit;
	int		i;

	i = 0;
	while (i < args()->nb_philo)
	{
		pthread_mutex_lock(&args()->prio);
		if (time_now() - args()->philos[i].last_meal >= args()->time_to_d)
		{
			if (!check_stop())
				printf("%ld %d died\n", time_now(), i);
			pthread_mutex_unlock(&args()->prio);
			pthread_mutex_lock(&args()->god);
			args()->stop = true;
			pthread_mutex_unlock(&args()->god);
			return (true);
		}
		pthread_mutex_unlock(&args()->prio);
		i++;
	}
	return (false);
}

bool	check_meals(int meals)
{
	if (meals == args()->nb_philo)
	{
		pthread_mutex_lock(&args()->god);
		args()->stop = true;
		pthread_mutex_unlock(&args()->god);
		return (true);
	}
	return (false);
}

void	monitor(void)
{
	int		i;
	int		meals;

	while (1)
	{
		i = 0;
		meals = 0;
		if (check_death())
			break ;
		if (args()->nb_times_e > 0)
		{
			pthread_mutex_lock(&args()->prio);
			while (i < args()->nb_philo)
			{
				if (args()->philos[i].n_meals >= args()->nb_times_e)
					meals++;
				i++;
			}
			pthread_mutex_unlock(&args()->prio);
			if (check_death())
				break ;
			if (check_meals(meals))
				break ;
		}
	}
}
