/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gufreire <gufreire@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 17:34:18 by gufreire          #+#    #+#             */
/*   Updated: 2025/10/27 18:11:19 by gufreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philos.h"

void	*start(void *arg)
{
	t_philo		*p;

	if (!arg)
		return (NULL);
	p = (t_philo *)arg;
	while (check_stop());
	if (args()->nb_philo == 1)
		return (one_case(p), NULL);
	if ((p->id % 2) == 0)
		usleep(100);
	while (1)
	{
		if (args()->nb_times_e > 0 && p->n_meals >= args()->nb_times_e)
			break ;
		if (check_stop())
			break ;
		eating(p);
		if (check_stop())
			break ;
		sleeping(p);
		if (check_stop())
			break ;
		thinking(p);
	}
	return (NULL);
}

int	main(int ac, char **av)
{
	int i;
	if (pars(ac, av) == false)
		return (1);
	if (!innit_everything())
		return (2);
	pthread_mutex_lock(&args()->god);
	args()->stop = false;
	args()->s_time = get_time();
	i = -1;
	while (++i < args()->nb_philo)
	{
		args()->philos[i].last_meal = args()->s_time;
	}
	pthread_mutex_unlock(&args()->god);
	clean();
	return (0);
}
