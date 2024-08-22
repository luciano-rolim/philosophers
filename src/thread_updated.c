/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_updated.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeneghe <lmeneghe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 12:33:22 by lmeneghe          #+#    #+#             */
/*   Updated: 2024/08/22 17:00:07 by lmeneghe         ###   ########.fr       */
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
	pthread_mutex_lock(&philo->mutex_last_meal);
	pthread_mutex_lock(philo->mutex_print);
	if (!all_alive(philo))
	{
		pthread_mutex_unlock(philo->mutex_print);
		pthread_mutex_unlock(&philo->mutex_last_meal);
		return ;
	}
	philo->last_meal = simulation_timestamp(philo->strt_tm);
	printf("%li %i has taken a fork\n%li %i is eating\n", philo->last_meal, philo->nbr, philo->last_meal, philo->nbr);
	philo->must_eat--;
	pthread_mutex_unlock(philo->mutex_print);
	pthread_mutex_unlock(&philo->mutex_last_meal);
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
		usleep(philo->time_to_eat);
		pthread_mutex_unlock(philo->grab_second);
		pthread_mutex_unlock(philo->grab_first);
		if (philo->eat_ending_set && !philo->must_eat)
			break ;
		custom_write(philo, "is sleeping\n");
		usleep(philo->time_to_sleep);
		regular_think_action(philo);
	}
	return (NULL);
}

void	*death_thread(void *data)
{
	t_prog *prog;
	int i;
	int	no_deaths;
	int	active_philos;

	prog = (t_prog *)data;
	no_deaths = 1;
	active_philos = prog->params.nbr_philos;
	while (time_mls() < prog->strt_tm)
		continue ;
	while (no_deaths && active_philos)
	{
		i = 0;
		active_philos = prog->params.nbr_philos;
		while (i < prog->params.nbr_philos)
		{
			pthread_mutex_lock(&prog->philos[i].mutex_last_meal);
			if ((prog->params.nbr_must_eat != -1) && !prog->philos[i].must_eat)
				active_philos--;
			else
			{
				if ((simulation_timestamp(prog->strt_tm) - (prog->philos[i].last_meal)) >= (prog->params.time_to_die / 1000))
				{
					pthread_mutex_lock(&prog->mutexes.printing);
					pthread_mutex_lock(&prog->mutexes.all_alive);
					prog->all_alive = 0;
					printf("%li %i died\n", simulation_timestamp(prog->strt_tm), prog->philos[i].nbr);
					pthread_mutex_unlock(&prog->mutexes.all_alive);
					pthread_mutex_unlock(&prog->mutexes.printing);
					pthread_mutex_unlock(&prog->philos[i].mutex_last_meal);
					no_deaths = 0;
					break;
				}
			}
			pthread_mutex_unlock(&prog->philos[i].mutex_last_meal);
			i++;
		}
		usleep(1);
	}
	return (NULL);
}

