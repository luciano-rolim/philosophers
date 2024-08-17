/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeneghe <lmeneghe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 14:57:26 by lmeneghe          #+#    #+#             */
/*   Updated: 2024/08/17 14:43:25 by lmeneghe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

// static int	remove_from_middle(t_prog *prog, t_philo *philo)
// {
// 	int	i;

// 	if (!prog || !philo)
// 		return (0);
// 	i = prog->queue.beggining;
// 	while (i < prog->queue.ending)
// 	{
// 		if (prog->queue.arr[i] == philo->nbr)
// 		{
// 			while (i > prog->queue.beggining)
// 			{
// 				prog->queue.arr[i] = prog->queue.arr[i - 1];
// 				i--;
// 			}
// 			prog->queue.beggining++;
// 			return (1);
// 		}
// 		i++;
// 	}
// 	return (0);
// }

// static void	adjust_queue(t_prog *prog)
// {
// 	int i;
// 	int j;

// 	i = 0;
// 	j = prog->queue.beggining;
// 	while (j <= prog->queue.ending)
// 		prog->queue.arr[i++] = prog->queue.arr[j++];
// 	prog->queue.beggining = 0;
// 	prog->queue.ending = i;
// }

// int	remove_from_queue(t_prog *prog, t_philo *philo)
// {
// 	if (!prog || !philo)
// 		return (0);
// 	pthread_mutex_lock(prog->mutexes.queue);
// 	if (prog->queue.size == 0)
// 	{
// 		pthread_mutex_unlock(prog->mutexes.queue);		
// 		return (print_error("Queue is empty. Nothing to remove\n"));
// 	}
// 	if (prog->queue.arr[prog->queue.beggining] != philo->nbr)
// 		remove_from_middle(prog, philo);
// 	else
// 		prog->queue.beggining++;
// 	prog->queue.size--;
// 	philo->on_queue = 0;
// 	pthread_mutex_unlock(prog->mutexes.queue);
// 	return (1);
// }

// int	add_to_queue(t_prog *prog, t_philo *philo)
// {
// 	if (!prog || !philo)
// 		return (0);
// 	pthread_mutex_lock(prog->mutexes.queue);
// 	if (prog->queue.size == prog->params.nbr_philos)
// 	{
// 		pthread_mutex_unlock(prog->mutexes.queue);
// 		return (print_error("Queue is full\n"));
// 	}
// 	prog->queue.arr[prog->queue.ending] = philo->nbr;
// 	if (prog->queue.ending == prog->queue.arr_last)
// 		adjust_queue(prog);
// 	else
// 		prog->queue.ending++;
// 	prog->queue.size++;
// 	philo->on_queue = 1;
// 	pthread_mutex_unlock(prog->mutexes.queue);
// 	return (1);
// }
