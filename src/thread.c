/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeneghe <lmeneghe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 15:03:37 by lmeneghe          #+#    #+#             */
/*   Updated: 2024/08/06 16:28:03 by lmeneghe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	is_priority(t_prog *prog, t_philo *philo)
{
	if (!prog || !philo)
		return (-1);
	if (is_even(philo->nbr) || (philo->nbr == prog->params.nbr_philos))
		return (0);
	else
		return (1);
}

void	philo_cicle(t_philo *philo, t_prog *prog)
{
	int	grab_first;
	int	grab_second;
	int	*first_fork;
	int	*second_fork;

	if (!philo || !prog)
		return ;
	grab_first = ft_lower(philo->index, philo->index_next);
	grab_second = ft_bigger(philo->index, philo->index_next);
	first_fork = &prog->mutexes.bool_forks[grab_first];
	second_fork = &prog->mutexes.bool_forks[grab_second];
	while (1)
	{
		pthread_mutex_lock(prog->mutexes.fork_availability);
		if (*first_fork == 0 && *second_fork == 0)
		{
			*first_fork = 1;
			*second_fork = 1;
			pthread_mutex_unlock(prog->mutexes.fork_availability);
			if (philo->is_thinking)
				philo->is_thinking = 0;
			pthread_mutex_lock(&prog->mutexes.forks[grab_first]);
			printf("%li %i has taken a fork\n", timestamp(prog), philo->nbr);
			pthread_mutex_lock(&prog->mutexes.forks[grab_second]);
			printf("%li %i has taken a fork\n", timestamp(prog), philo->nbr);
			philo->eat_count++;
			if (is_priority(prog, philo) && philo->eat_count == 1)
			{
				pthread_mutex_lock(prog->mutexes.eat_first_count);
				prog->eat_first_line--;
				pthread_mutex_unlock(prog->mutexes.eat_first_count);
			}
			printf("%li %i is eating\n", timestamp(prog), philo->nbr);
			usleep(prog->params.time_to_eat * 1000);
			pthread_mutex_lock(prog->mutexes.fork_availability);
			*first_fork = 0;
			*second_fork = 0;
			pthread_mutex_unlock(prog->mutexes.fork_availability);
			pthread_mutex_unlock(&prog->mutexes.forks[grab_first]);
			pthread_mutex_unlock(&prog->mutexes.forks[grab_second]);
			if (prog->params.nbr_must_eat != -1 && \
			philo->eat_count == philo->must_eat)
				break ;
			printf("%li %i is sleeping\n", timestamp(prog), philo->nbr);
			usleep(prog->params.time_to_sleep * 1000);
		}
		else
		{
			pthread_mutex_unlock(prog->mutexes.fork_availability);
			if (!philo->is_thinking)
			{
				printf("%li %i is thinking\n", timestamp(prog), philo->nbr);
				philo->is_thinking = 1;
			}
			usleep(500);
		}
	}
}

void	priority_line_check(t_prog *prog, t_philo *philo)
{
	if (!is_priority(prog, philo))
	{
		while (1)
		{
			pthread_mutex_lock(prog->mutexes.eat_first_count);
			if (prog->eat_first_line == 0)
			{
				pthread_mutex_unlock(prog->mutexes.eat_first_count);
				break ;
			}
			else
			{
				pthread_mutex_unlock(prog->mutexes.eat_first_count);
				usleep(500);
			}
		}
	}
}

void	*philo_thread(void *data)
{
	t_philo	*philo;
	t_prog	*prog;

	if (!data)
		return (print_error_pointer("Thread Error: data pointer is NULL\n"));
	philo = (t_philo *)data;
	prog = (t_prog *)(philo->prog);
	if (!philo || !prog)
		return (print_error_pointer("Error: philo or prog pointer is NULL\n"));
	priority_line_check(prog, philo);
	philo_cicle(philo, prog);
	return (NULL);
}

//Replace both usleep(500) by some proper shit, like a line 
// or shit like that, or maybe reduce time