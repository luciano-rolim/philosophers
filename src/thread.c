/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeneghe <lmeneghe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 15:03:37 by lmeneghe          #+#    #+#             */
/*   Updated: 2024/08/21 14:03:38 by lmeneghe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

// int	think_action(t_prog *prog, t_philo *philo)
// {
// 	pthread_mutex_lock(prog->mutexes.printing);
// 	if (!prog->all_alive)
// 	{
// 		pthread_mutex_unlock(prog->mutexes.printing);
// 		return (0);
// 	}
// 	printf("%li %i is thinking\n", simulation_timestamp(philo->tmp_time, philo->strt_tm), philo->nbr);
// 	pthread_mutex_unlock(prog->mutexes.printing);
// 	return (1);
// }

// void	odd_thinking(t_prog *prog, t_philo *philo)
// {
// 	if (philo->wait_one_remaining > 0)
// 	{
// 		think_action(prog, philo);
// 		usleep(((prog->params.time_to_eat) - (prog->params.time_to_sleep)) - 1000);
// 		philo->wait_one_remaining--;
// 	}
// 	else
// 	{
// 		think_action(prog, philo);
// 		usleep((prog->params.time_to_eat * 2) - prog->params.time_to_sleep - 1000);
// 		philo->wait_one_remaining = philo->max_wait_one_remaining;
// 	}
// 	//again, stupid shit of wheter sleep is bigger or even equal to eat, what to do in each scenario	
// }

// void	death_calculus(t_prog *prog, t_philo *philo)
// {
// 	if ((simulation_timestamp(philo->tmp_time, philo->strt_tm) - philo->last_meal) >= philo->time_to_die)
// 	{
// 		pthread_mutex_lock(prog->mutexes.printing);
// 		pthread_mutex_lock(prog->mutexes.all_alive);
// 		if (!prog->all_alive)
// 		{
// 			pthread_mutex_unlock(prog->mutexes.all_alive);	
// 			pthread_mutex_unlock(prog->mutexes.printing);
// 			return ;
// 		}
// 		prog->all_alive = 0;
// 		pthread_mutex_unlock(prog->mutexes.all_alive);
// 		printf("%li %i died\n", simulation_timestamp(philo->tmp_time, philo->strt_tm), philo->nbr);
// 		pthread_mutex_unlock(prog->mutexes.printing);
// 	}
// }

// void	*philo_thread(void *data)
// {
// 	t_philo	*philo;
// 	t_prog	*prog;

// 	philo = (t_philo *)data;
// 	prog = (t_prog *)(philo->prog);
// 	philo->strt_tm = prog->strt_tm;
// 	philo->last_meal = 0;
// 	death_calculus(prog, philo);
// 	if (philo->start_position == 2)
// 	{
// 		if (!think_action(prog, philo))
// 			return (NULL);
// 		usleep(prog->params.time_to_eat - 1000);
// 	}
// 	else if (philo->start_position == 3)
// 	{
// 		if(!think_action(prog, philo))
// 			return (NULL);
// 		usleep((prog->params.time_to_eat * 2) - 1000);
// 	}
// 	philo_cicle(philo, prog);
// 	return (NULL);
// }

//shit corner case 0 necessity to eat
//start thinking other shit corner cases
//other corner case, time to eat same as time to sleep, causing corner case ./a.out 5 0 100 100 2