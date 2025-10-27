/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gufreire <gufreire@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 17:51:47 by gufreire          #+#    #+#             */
/*   Updated: 2025/10/27 18:01:48 by gufreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philos.h"

bool	get_forks(t_philo *p)
{
	if (check_stop())
		return (false);
	if (p->id == 0)
	{
		pthread_mutex_lock(&args()->forks[args()->nb_philo - 1]);
		pthread_mutex_lock(&args()->forks[p->id]);
	}
	else
	{
		pthread_mutex_lock(&args()->forks[p->id]);
		pthread_mutex_lock(&args()->forks[p->id - 1]);
	}
	if (check_stop())
	{
		drop_forks(p);
		return (false);
	}
	pthread_mutex_lock(&args()->prio);
	if (!check_stop())
	{
		printf("%ld %d has taken a fork\n", time_now(), p->id + 1);
		printf("%ld %d has taken a fork\n", time_now(), p->id + 1);
	}
	pthread_mutex_unlock(&args()->prio);
	return (true);
}

void	drop_forks(t_philo *p)
{
	if (p->id == 0)
	{
		pthread_mutex_unlock(&args()->forks[p->id]);
		pthread_mutex_unlock(&args()->forks[args()->nb_philo - 1]);
	}
	else
	{
		pthread_mutex_unlock(&args()->forks[p->id - 1]);
		pthread_mutex_unlock(&args()->forks[p->id]);
	}
}
