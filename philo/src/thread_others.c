/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_others.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeneghe <lmeneghe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 15:32:03 by lmeneghe          #+#    #+#             */
/*   Updated: 2024/08/26 16:04:42 by lmeneghe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	*lone_philo(void *data)
{
	t_philo	*philo;
	t_prog	*prog;

	philo = (t_philo *)data;
	prog = (t_prog *)philo->prog;
	philo->strt_tm_micros = prog->strt_tm_micros;
	delay_to_start(philo);
	custom_write(philo, "is thinking\n");
	return (NULL);
}

static void	death_execution(t_prog *prog, struct timeval tmp_time, int i)
{
	pthread_mutex_lock(&prog->mutexes.printing);
	prog->all_alive = 0;
	printf("%li %i died\n", \
	timestamp(prog->strt_tm_micros, tmp_time), prog->philos[i].nbr);
	pthread_mutex_unlock(&prog->mutexes.printing);
	pthread_mutex_unlock(&prog->philos[i].mutex_last_meal);
	prog->no_deaths = 0;
}

static void	death_loop(t_prog *prog, int philos_on, int i)
{
	struct timeval	tmp_time;

	while (prog->no_deaths && philos_on)
	{
		i = 0;
		philos_on = prog->params.nbr_philos;
		while (i < prog->params.nbr_philos)
		{
			pthread_mutex_lock(&prog->philos[i].mutex_last_meal);
			if ((prog->params.nbr_must_eat != -1) && !prog->philos[i].must_eat)
				philos_on--;
			else
			{
				if ((timestamp(prog->strt_tm_micros, tmp_time) \
				- (prog->philos[i].last_meal) >= prog->params.time_to_die_mls))
				{
					death_execution(prog, tmp_time, i);
					break ;
				}
			}
			pthread_mutex_unlock(&prog->philos[i].mutex_last_meal);
			i++;
		}
		usleep(1);
	}
}

void	*death_thread(void *data)
{
	t_prog			*prog;
	int				i;
	int				philos_on;

	prog = (t_prog *)data;
	philos_on = prog->params.nbr_philos;
	i = 0;
	while (time_in_microseconds() < prog->strt_tm_micros)
		continue ;
	death_loop(prog, philos_on, i);
	return (NULL);
}
