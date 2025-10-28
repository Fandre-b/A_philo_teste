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
		if ( timestamp - args()->philos[i].last_meal >= args()->time_to_d)
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
	bool value;

	value = true;
	pthread_mutex_lock(&args()->prio);	
	if (args()->nb_times_e > 0 && p->n_meals >= args()->nb_times_e)
	{
		printf("philo %i is full, cant die\n", p->id + 1);
		value = false;
	}
	timestamp = time_now();
	if (value && timestamp - p->last_meal >= args()->time_to_d)
	{
		if (!check_stop())
		{
			printf("ID: %d last meal was at timestamp: %ld, dude eaten %d times\n", p->id + 1, p->last_meal, p->n_meals);
			printf("%ld %d died\n", timestamp, p->id + 1);
		}
		pthread_mutex_lock(&args()->god);
		args()->stop = true;
		pthread_mutex_unlock(&args()->god);
		value = true;
	}
	pthread_mutex_unlock(&args()->prio);
	value = false;
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
		pthread_mutex_unlock(&args()->prio);
		i = (i + 1) % args()->nb_philo;
		if (check_meals(meals))
			break ;
		// if (check_death())
		// 	break ;
	}
	return (NULL);
}
