/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_updated.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeneghe <lmeneghe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 12:33:22 by lmeneghe          #+#    #+#             */
/*   Updated: 2024/08/22 12:27:01 by lmeneghe         ###   ########.fr       */
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

void	custom_write(t_philo *philo, char *message)
{
	pthread_mutex_lock(philo->mutex_print);
	if (!all_alive(philo))
	{
		pthread_mutex_unlock(philo->mutex_print);
		return ;
	}
	printf("%li %i %s", simulation_timestamp(philo->strt_tm), philo->nbr, message);
	pthread_mutex_unlock(philo->mutex_print);	
}

void	regular_think_action(t_philo *philo)
{
	custom_write(philo, "is thinking\n");
	if (philo->time_to_sleep < philo->time_to_eat)
		usleep(philo->time_to_eat - philo->time_to_sleep - 1000);
}

void	write_fork_eat_action(t_philo *philo)
{
	long int	timestamp;

	pthread_mutex_lock(philo->mutex_print);
	if (!all_alive(philo))
	{
		pthread_mutex_unlock(philo->mutex_print);
		return ;
	}
	timestamp = simulation_timestamp(philo->strt_tm);
	printf("%li %i has taken a fork\n%li %i is eating\n", timestamp, philo->nbr, timestamp, philo->nbr);
	pthread_mutex_unlock(philo->mutex_print);
}

void	*philo_thread(void *data)
{
	t_philo	*philo;
	t_prog	*prog;

	philo = (t_philo *)data;
	prog = (t_prog *)philo->prog;
	philo->strt_tm = prog->strt_tm;
	if (philo->nbr % 2 == 0)
	{
		delay_to_start(philo);
		custom_write(philo, "is thinking\n");
		usleep(philo->time_to_eat - 2000);
	}
	else
		delay_to_start(philo);
	while (all_alive(philo))
	{
		pthread_mutex_lock(philo->grab_first);
		custom_write(philo, "has taken a fork\n");
		pthread_mutex_lock(philo->grab_second);
		write_fork_eat_action(philo);
		philo->eat_count++;
		usleep(philo->time_to_eat);
		pthread_mutex_unlock(philo->grab_second);
		pthread_mutex_unlock(philo->grab_first);
		if (philo->eat_ending_set && (philo->eat_count == philo->must_eat))
			break ;
		custom_write(philo, "is sleeping\n");
		usleep(philo->time_to_sleep);
		regular_think_action(philo);
	}
	return (NULL);
}
