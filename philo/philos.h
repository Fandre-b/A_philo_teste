/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gufreire <gufreire@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 17:32:20 by gufreire          #+#    #+#             */
/*   Updated: 2025/10/27 18:12:12 by gufreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOS_H
# define PHILOS_H

# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <limits.h>
# include <stdbool.h>
# include <sys/time.h>
# ifndef DEBUG
#  define DEBUG 0
# endif

typedef struct s_threads
{
	int		id;
	int		n_meals;
	int		last_meal;

}		t_philo;

//args struct
typedef struct s_args
{
	int				nb_philo;
	int				time_to_d;
	int				time_to_e;
	int				time_to_s;
	int				nb_times_e;
	long			s_time;
	bool			stop;
	t_philo			*philos;
	pthread_t		*threads;
	pthread_mutex_t	*forks;
	pthread_mutex_t	god;
	pthread_mutex_t	prio;
}		t_args;

//fork functions
bool	get_forks(t_philo *p);
void	drop_forks(t_philo *p);

//innit functions
bool	innit_threads(void);
t_philo	innit_philos(int i);
bool	innit_mutexes(void);
bool	innit_structs(void);
bool	innit_everything(void);
void	*start(void *arg);
void	one_case(t_philo *p);
void	print_messages(t_philo *p, char c);
void	thinking(t_philo *p);
void	sleeping(t_philo *p);
void	eating(t_philo *p);

//parsing
bool	args_pars(char **av);
int		atoi_args(char *nb);
bool	pars(int ac, char **av);

//philo_utils functions
void	clean(void);
bool	check_stop(void);
bool	check_death(void);
void	monitor(void);

//routine functions
void	*start(void *arg);

//time functions
t_args	*args(void);
long	time_now(void);
long	get_time(void);

#endif