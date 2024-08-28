/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_death.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeneghe <lmeneghe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 15:32:03 by lmeneghe          #+#    #+#             */
/*   Updated: 2024/08/28 13:52:28 by lmeneghe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int exit_gracefully(t_prog *prog, t_philo *philo)
{
	pthread_join(prog->death_checker, NULL);
	children_close_sems(prog, philo);
	exit(EXIT_SUCCESS);
}

int exit_starvation(t_prog *prog, t_philo *philo)
{
	children_close_sems(prog, philo);
	exit(EXIT_FAILURE);
}

static void	death_execution(t_prog *prog, struct timeval tmp_time, t_philo *philo)
{
	sem_wait(prog->sems.printing);
	printf("%li %i died\n", timestamp(prog->strt_tm_micros, tmp_time), philo->nbr);
	// sem_post(prog->sems.printing);
}

static void	death_loop(t_philo *philo, t_prog *prog)
{
	struct timeval	tmp_time;

	while (1)
	{
		sem_wait(philo->sem_last_meal);
		if (philo->eat_ending_set && !philo->must_eat)
		{
			sem_post(philo->sem_last_meal);
			break ;
		}
		else
		{
			if ((timestamp(philo->strt_tm_micros, tmp_time) \
			- (philo->last_meal) >= prog->params.time_to_die_mls))
			{
				death_execution(prog, tmp_time, philo);
				sem_post(philo->sem_last_meal);
				exit_starvation(prog, philo);
			}
		}
		sem_post(philo->sem_last_meal);
		usleep(300);
	}
}

void	*death_thread(void *data)
{
	t_philo		*philo;
	t_prog		*prog;
	
	philo = (t_philo *)data;
	prog = (t_prog *)philo->prog;
	while (time_in_microseconds() < prog->strt_tm_micros)
		continue ;
	death_loop(philo, prog);
	return (NULL);
}
