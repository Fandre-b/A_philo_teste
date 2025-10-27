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
	if (pthread_join(*args()->routine_thread, NULL))
		return ;
	while (!check_stop())
		usleep(1000);
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
	bool val;
	pthread_mutex_lock(&args()->god);
	val = args()->stop;
	pthread_mutex_unlock(&args()->god);
	return (val);
}

bool	check_death(void)
{
	long	timestamp;
	int		i;

	i = 0;
	while (i < args()->nb_philo)
	{
		timestamp = time_now();
		pthread_mutex_lock(&args()->prio);
		if (timestamp - args()->philos[i].last_meal >= args()->time_to_d)
		{
			if (!check_stop())
				printf("%ld %d died\n", timestamp, i);
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

bool	check_philo_death(t_philo *p)
{
	long	timestamp;

	timestamp = time_now();
	pthread_mutex_lock(&args()->prio);
	if (timestamp - p->last_meal >= args()->time_to_d)
	{
		if (!check_stop())
			printf("%ld %d died\n", timestamp, p->id + 1);
		pthread_mutex_unlock(&args()->prio);
		pthread_mutex_lock(&args()->god);
		args()->stop = true;
		pthread_mutex_unlock(&args()->god);
		return (true);
	}
	pthread_mutex_unlock(&args()->prio);
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

void*	monitor(void *arg)
{
	int		i;
	int		meals;

	(void)arg;
	while (check_stop());
	i = 0;
	while (!check_stop())
	{
		if (i == 0)
			meals = 0;
		// if (check_death())
		if (check_philo_death(&args()->philos[i]))
			break ;
		if (args()->nb_times_e == 0)
		{
			continue;
		}
		pthread_mutex_lock(&args()->prio);
		if (args()->philos[i].n_meals >= args()->nb_times_e)
			meals++;
		i = (i + 1) % args()->nb_philo;
		pthread_mutex_unlock(&args()->prio);
		if (check_meals(meals))
			break ;
		// if (check_death())
		// 	break ;
		usleep(1000);
	}
	return (NULL);
}
