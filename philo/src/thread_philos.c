/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_philos.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeneghe <lmeneghe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 12:33:22 by lmeneghe          #+#    #+#             */
/*   Updated: 2024/08/28 14:46:53 by lmeneghe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	think_action(t_philo *philo)
{
	custom_write(philo, "is thinking\n");
	if (philo->even_prog)
		usleep(philo->time_to_think);
	else
	{
		if (philo->wait_one_remaining > 0)
		{
			usleep(philo->time_to_think);
			philo->wait_one_remaining--;
		}
		else
		{
			usleep(philo->time_to_double_think);
			philo->wait_one_remaining = philo->max_wait_one_remaining;
		}
	}
}

void	write_fork_eat_action(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex_last_meal);
	pthread_mutex_lock(philo->mutex_print);
	if (!(*philo->all_alive))
	{
		philo->eat_ending_set = 1;
		philo->must_eat = 0;
		pthread_mutex_unlock(philo->mutex_print);
		pthread_mutex_unlock(&philo->mutex_last_meal);
		return ;
	}
	philo->last_meal = timestamp(philo->strt_tm_micros, philo->tmp_time);
	printf("%li %i has taken a fork\n%li %i is eating\n", \
	philo->last_meal, philo->nbr, philo->last_meal, philo->nbr);
	philo->must_eat--;
	pthread_mutex_unlock(philo->mutex_print);
	pthread_mutex_unlock(&philo->mutex_last_meal);
	usleep(philo->time_to_eat);
}

static void	initial_set(t_philo *philo)
{
	if (philo->start_position == 2)
	{
		delay_to_start(philo);
		custom_write(philo, "is thinking\n");
		if (philo->time_to_eat > 0)
			usleep(philo->time_to_eat - TIME_REDUCE);
	}
	else if (philo->start_position == 3)
	{
		delay_to_start(philo);
		custom_write(philo, "is thinking\n");
		if (philo->time_to_eat > 0)
			usleep((philo->time_to_eat * 2) - TIME_REDUCE);
	}
	else
		delay_to_start(philo);
}

void	*philo_thread(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	initial_set(philo);
	while (1)
	{
		pthread_mutex_lock(philo->grab_first);
		custom_write(philo, "has taken a fork\n");
		pthread_mutex_lock(philo->grab_second);
		write_fork_eat_action(philo);
		pthread_mutex_unlock(philo->grab_second);
		pthread_mutex_unlock(philo->grab_first);
		if (philo->eat_ending_set && !philo->must_eat)
			break ;
		custom_write(philo, "is sleeping\n");
		usleep(philo->time_to_sleep);
		think_action(philo);
	}
	return (NULL);
}
