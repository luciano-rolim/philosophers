/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeneghe <lmeneghe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 15:03:37 by lmeneghe          #+#    #+#             */
/*   Updated: 2024/08/17 15:26:38 by lmeneghe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	eating_action(t_prog *prog, t_philo *philo)
{
	pthread_mutex_lock(&prog->mutexes.forks[philo->grab_first]);
	pthread_mutex_lock(&prog->mutexes.forks[philo->grab_second]);
	//pthread_mutex_lock(prog->mutexes.printing);
	printf("%li %i has taken a fork\n", timestamp(prog), philo->nbr);
	printf("%li %i has taken a fork\n", timestamp(prog), philo->nbr);
	printf("%li %i is eating\n", timestamp(prog), philo->nbr);
	//pthread_mutex_unlock(prog->mutexes.printing);
	philo->eat_count++;
	usleep(prog->params.time_to_eat);
	pthread_mutex_unlock(&prog->mutexes.forks[philo->grab_first]);
	pthread_mutex_unlock(&prog->mutexes.forks[philo->grab_second]);
}

void think_action(t_prog *prog, t_philo *philo)
{
	//pthread_mutex_lock(prog->mutexes.printing);
	printf("%li %i is thinking\n", timestamp(prog), philo->nbr);
	//pthread_mutex_unlock(prog->mutexes.printing);
}

void sleep_action(t_prog *prog, t_philo *philo)
{
	//pthread_mutex_lock(prog->mutexes.printing);
	printf("%li %i is sleeping\n", timestamp(prog), philo->nbr);
	//pthread_mutex_unlock(prog->mutexes.printing);
	usleep(prog->params.time_to_sleep);
}

void	even_thinking(t_prog *prog, t_philo *philo)
{
	if (prog->params.time_to_sleep < prog->params.time_to_eat)
	{
		think_action(prog, philo);
		usleep(((prog->params.time_to_eat) - (prog->params.time_to_sleep)) - 1000);
	}
	//wat is is not? sleep is bigger than eat? what now? just go eat? always? this shit is causing dealock
}

void	odd_thinking(t_prog *prog, t_philo *philo)
{
	if (philo->wait_one_remaining > 0)
	{
		think_action(prog, philo);
		usleep(((prog->params.time_to_eat) - (prog->params.time_to_sleep)) - 1000);
		philo->wait_one_remaining--;
	}
	else
	{
		think_action(prog, philo);
		usleep((prog->params.time_to_eat * 2) - prog->params.time_to_sleep - 1000);
		philo->wait_one_remaining = philo->max_wait_one_remaining;
	}
	//again, stupid shit of wheter sleep is bigger or even equal to eat, what to do in each scenario	
}

void	philo_cicle(t_philo *philo, t_prog *prog)
{
	while (1)
	{
		eating_action(prog, philo);
		if (prog->params.nbr_must_eat != -1 && philo->eat_count == philo->must_eat)
			break ;
		sleep_action(prog, philo);
		if (philo->even_prog)
			even_thinking(prog, philo);
		else
			odd_thinking(prog, philo);
	}
}

void	*philo_thread(void *data)
{
	t_philo	*philo;
	t_prog	*prog;

	// if (!data)
	// 	return (print_error_pointer("Thread Error: data pointer is NULL\n"));
	philo = (t_philo *)data;
	prog = (t_prog *)(philo->prog);
	if (philo->start_position == 2)
	{
		think_action(prog, philo);
		usleep(prog->params.time_to_eat - 1000);
	}
	else if (philo->start_position == 3)
	{
		think_action(prog, philo);
		usleep((prog->params.time_to_eat * 2) - 1000);			
	}
	philo_cicle(philo, prog);
	return (NULL);
}

//shit corner case 0 necessity to eat
//start thinking other shit corner cases
//other corner case, time to eat same as time to sleep, causing corner case ./a.out 5 0 100 100 2