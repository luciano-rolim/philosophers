/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_philos.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeneghe <lmeneghe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 12:33:22 by lmeneghe          #+#    #+#             */
/*   Updated: 2024/08/27 14:15:05 by lmeneghe         ###   ########.fr       */
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

static void	initial_delay(t_philo *philo)
{
	if (philo->start_position == 2)
	{
		delay_to_start(philo);
		custom_write(philo, "is thinking\n");
		if (philo->time_to_eat > 0)
			usleep(philo->time_to_eat - 900);
	}
	else if (philo->start_position == 3)
	{
		delay_to_start(philo);
		custom_write(philo, "is thinking\n");
		if (philo->time_to_eat > 0)
			usleep((philo->time_to_eat * 2) - 900);
	}
	else
		delay_to_start(philo);
}

static int	philo_nbr_attribution(t_prog *prog)
{
	int i;
	int	philo_nbr;

	if (!prog)initial_delay
	{
		if (!prog->philo_attribution)
		{
			philo_nbr = i + 1;
			sem_post(&prog->semaphores.counter);		
			break;
		}
		else
			i++;
	}
	sem_post(&prog->semaphores.counter);
}

static int	philo_init(t_prog *prog, t_philo *philo)
{
	if (!prog || !philo)
		return (print_error("Error on philo_init call\n"));
	if (!philo_variables_init(prog, philo))
		return (0);
	if (!grab_fork_order(prog, philo))
		return (0);
	if (!start_position(prog, philo))
		return (0);
	if (!calculus_wait_one_remaining(prog, philo))
		return (0);
	if (!mutex_init(&philo->mutex_last_meal))
		return (0);
	if (!calculus_time_to_think(prog, philo))
		return (0);
	return (1);
}

void	*philo_process(t_prog *prog, int i)
{
	t_philo	philo;
	int		philo_nbr;


	philo_nbr = philo_nbr_attribution(prog);
	philo = prog->philos[i];
	philo_init(prog, &philo);
	initial_delay(&philo);
	while (1)
	{
		sem_wait(prog->semaphores.forks);


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
