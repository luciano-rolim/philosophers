/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeneghe <lmeneghe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 15:03:37 by lmeneghe          #+#    #+#             */
/*   Updated: 2024/08/09 15:02:34 by lmeneghe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	eating_action(t_prog *prog, t_philo *philo)
{
	if (!prog || !philo)
		return ;
	pthread_mutex_lock(&prog->mutexes.forks[philo->grab_first]);
	pthread_mutex_lock(prog->mutexes.printing);
	printf("%li %i has taken a fork\n", timestamp(prog), philo->nbr);
	pthread_mutex_unlock(prog->mutexes.printing);
	pthread_mutex_lock(&prog->mutexes.forks[philo->grab_second]);
	pthread_mutex_lock(prog->mutexes.printing);
	printf("%li %i has taken a fork\n", timestamp(prog), philo->nbr);
	pthread_mutex_unlock(prog->mutexes.printing);
	philo->eat_count++;
	if (philo->eat_count == 1 && philo->eat_first_priority)
	{
		pthread_mutex_lock(prog->mutexes.eat_first_count);
		prog->eat_first_line--;
		pthread_mutex_unlock(prog->mutexes.eat_first_count);
	}
	pthread_mutex_lock(prog->mutexes.printing);
	printf("%li %i is eating\n", timestamp(prog), philo->nbr);
	pthread_mutex_unlock(prog->mutexes.printing);
	usleep(prog->params.time_to_eat * 1000);
}

void	eating_process(t_prog *prog, t_philo *philo)
{
	while (1)
	{
		pthread_mutex_lock(prog->mutexes.fork_availability);
		if (*philo->bool_1 == 0 && *philo->bool_2 == 0)
		{
			*philo->bool_1 = 1;
			*philo->bool_2 = 1;
			pthread_mutex_unlock(prog->mutexes.fork_availability);
			philo->is_thinking = 0;
			remove_from_queue(prog, philo);
			eating_action(prog, philo);
			pthread_mutex_lock(prog->mutexes.fork_availability);
			*philo->bool_1 = 0;
			*philo->bool_2 = 0;
			pthread_mutex_unlock(prog->mutexes.fork_availability);
			pthread_mutex_unlock(&prog->mutexes.forks[philo->grab_first]);
			pthread_mutex_unlock(&prog->mutexes.forks[philo->grab_second]);
			break ;
		}
		else
		{
			pthread_mutex_unlock(prog->mutexes.fork_availability);
			if (!philo->is_thinking)
			{
				pthread_mutex_lock(prog->mutexes.printing);
				printf("%li %i is thinking\n", timestamp(prog), philo->nbr);
				pthread_mutex_unlock(prog->mutexes.printing);
				philo->is_thinking = 1;
			}
			usleep(300);
		}
	}
}

int	has_resource_priority(t_prog *prog, t_philo *philo)
{
	int i;

	if (!prog || !philo)
		return (0);
	pthread_mutex_lock(prog->mutexes.queue);
	i = prog->queue.beggining;
	while (i < prog->queue.ending)
	{
		if (prog->queue.arr[i] == philo->nbr)
		{
			pthread_mutex_unlock(prog->mutexes.queue);
			return (1);
		}
		else
		{
			if (prog->queue.arr[i] == philo->prev || prog->queue.arr[i] == philo->next)
			{
				pthread_mutex_unlock(prog->mutexes.queue);
				return (0);
			}
		}
		i++;
	}
	pthread_mutex_unlock(prog->mutexes.queue);
	return (0);
}

void	philo_cicle(t_philo *philo, t_prog *prog)
{
	if (!philo || !prog)
		return ;
	while (1)
	{
		if (!philo->on_queue)
			add_to_queue(prog, philo);
		if (has_resource_priority(prog, philo))
		{
			eating_process(prog, philo);
			if (prog->params.nbr_must_eat != -1 && philo->eat_count == philo->must_eat)
				break ;
			pthread_mutex_lock(prog->mutexes.printing);
			printf("%li %i is sleeping\n", timestamp(prog), philo->nbr);
			pthread_mutex_unlock(prog->mutexes.printing);
			usleep(prog->params.time_to_sleep * 1000);
		}
		else
		{
			if (!philo->is_thinking)
			{
				pthread_mutex_lock(prog->mutexes.printing);
				printf("%li %i is thinking\n", timestamp(prog), philo->nbr);
				pthread_mutex_unlock(prog->mutexes.printing);
				philo->is_thinking = 1;
			}
			usleep(300);
		}
	}
}

void	priority_line_check(t_prog *prog, t_philo *philo)
{
	if (!philo->eat_first_priority)
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
				usleep(300);
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
