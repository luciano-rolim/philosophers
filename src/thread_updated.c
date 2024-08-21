/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_updated.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeneghe <lmeneghe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 12:33:22 by lmeneghe          #+#    #+#             */
/*   Updated: 2024/08/21 15:58:20 by lmeneghe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int all_alive(t_philo *philo)
{
	pthread_mutex_lock(philo->mutex_all_alive);
	if (*philo->all_alive)
	{
		pthread_mutex_unlock(philo->mutex_all_alive);
		return (1);
	}
	pthread_mutex_unlock(philo->mutex_all_alive);
	return (0);
}

void	delay_to_start(t_philo *philo)
{
	while (time_mls() < philo->strt_tm)
		continue ;
}

// int	think_action(t_prog *philo)
// {

// 	return (1);
// }

void	write_fork_action(t_philo *philo)
{
	pthread_mutex_lock(philo->mutex_print);
	if (!all_alive(philo))
	{
		pthread_mutex_unlock(philo->mutex_print);
		return ;
	}
	printf("%li %i has taken a fork\n", simulation_timestamp(philo->tmp_time, philo->strt_tm), philo->nbr);
	pthread_mutex_unlock(philo->mutex_print);
}

void	write_fork_eat_action(t_philo *philo)
{
	pthread_mutex_lock(philo->mutex_print);
	if (!all_alive(philo))
	{
		pthread_mutex_unlock(philo->mutex_print);
		return ;
	}
	printf("%li %i has taken a fork\n%li %i is eating\n", simulation_timestamp(philo->tmp_time, philo->strt_tm), philo->nbr, simulation_timestamp(philo->tmp_time, philo->strt_tm), philo->nbr);
	pthread_mutex_unlock(philo->mutex_print);
}

void	write_sleep_action(t_philo *philo)
{
	pthread_mutex_lock(philo->mutex_print);
	if (!all_alive(philo))
	{
		pthread_mutex_unlock(philo->mutex_print);
		return ;
	}
	printf("%li %i is sleeping\n", simulation_timestamp(philo->tmp_time, philo->strt_tm), philo->nbr);
	pthread_mutex_unlock(philo->mutex_print);
}

int	eat_sleep_action(t_prog *prog, t_philo *philo)
{
	pthread_mutex_lock(philo->grab_first);
	write_fork_action(philo); //check for return or shit like that?
	pthread_mutex_lock(philo->grab_second);
	write_fork_eat_action(philo);
	philo->eat_count++;
	usleep(prog->params.time_to_eat);
	pthread_mutex_unlock(philo->grab_second);
	pthread_mutex_unlock(philo->grab_first); //test if, in case of altering the unlocking order (first second first second ao inves de first second second first) if it causes helgrind shit
	if (philo->eat_ending_set && (philo->eat_count == philo->must_eat))
		return (0);
	write_sleep_action(philo);
	usleep(prog->params.time_to_sleep);
	return (1);
}

void	*philo_thread(void *data)
{
	t_philo	*philo;
	t_prog	*prog;

	philo = (t_philo *)data;
	prog = (t_prog *)philo->prog;
	philo->strt_tm = prog->strt_tm;
	delay_to_start(philo);
	// if (philo->nbr % 2 == 0)
	// 	think_action(philo);
	while (all_alive(philo))
	{
		if (!eat_sleep_action(prog, philo))
			break ;
	}
	prog = (t_prog *)(philo->prog);
	return (NULL);
}
