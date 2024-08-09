/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeneghe <lmeneghe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 15:03:37 by lmeneghe          #+#    #+#             */
/*   Updated: 2024/08/09 14:55:34 by lmeneghe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

// void print_array(t_prog *prog, char *message)
// {
// 	int i;

// 	i = prog->queue.beggining;
// 	if (message)
// 		printf("%s", message);
// 	while (i < prog->queue.ending)
// 		printf("%i\n", prog->queue.arr[i++]);
// 	printf("Array finished\n");
// }

int	is_priority(t_prog *prog, t_philo *philo)
{
	if (!prog || !philo)
		return (-1);
	if (is_even(philo->nbr) || (philo->nbr == prog->params.nbr_philos))
		return (0);
	else
		return (1);
}

int	remove_from_middle(t_prog *prog, t_philo *philo)
{
	int	i;

	if (!prog || !philo)
		return (0);
	i = prog->queue.beggining;
	while (i < prog->queue.ending)
	{
		if (prog->queue.arr[i] == philo->nbr)
		{
			while (i > prog->queue.beggining)
			{
				prog->queue.arr[i] = prog->queue.arr[i - 1];
				i--;
			}
			prog->queue.beggining++;
			return (1);
		}
		i++;
	}
	return (0);
}

int	remove_queue(t_prog *prog, t_philo *philo)
{
	if (!prog || !philo)
		return (0);
	pthread_mutex_lock(prog->mutexes.queue);
	if (prog->queue.size == 0)
	{
		pthread_mutex_unlock(prog->mutexes.queue);		
		return (print_error("Queue is empty. Nothing to remove\n"));
	}
	if (prog->queue.arr[prog->queue.beggining] != philo->nbr)
		remove_from_middle(prog, philo);
	else
		prog->queue.beggining++;
	prog->queue.size--;
	philo->on_queue = 0;
	// printf("Printing array after removing %i from queue\n", philo->nbr);
	// print_array(prog, NULL);
	pthread_mutex_unlock(prog->mutexes.queue);
	return (1);
}

void	adjust_list(t_prog *prog)
{
	int i;
	int j;

	i = 0;
	j = prog->queue.beggining;
	while (j <= prog->queue.ending)
		prog->queue.arr[i++] = prog->queue.arr[j++];
	prog->queue.beggining = 0;
	prog->queue.ending = i;
}

int	add_queue(t_prog *prog, t_philo *philo)
{
	if (!prog || !philo)
		return (0);
	pthread_mutex_lock(prog->mutexes.queue);
	if (prog->queue.size == prog->params.nbr_philos)
	{
		pthread_mutex_unlock(prog->mutexes.queue);
		return (print_error("Queue is full\n"));
	}
	prog->queue.arr[prog->queue.ending] = philo->nbr;
	if (prog->queue.ending == prog->queue.arr_last)
		adjust_list(prog);
	else
		prog->queue.ending++;
	prog->queue.size++;
	philo->on_queue = 1;
	// printf("Printing array after adding %i on queue\n", philo->nbr);
	// print_array(prog, NULL);
	pthread_mutex_unlock(prog->mutexes.queue);
	return (1);
}

void	eating(t_prog *prog, t_philo *philo, int grab_first, int grab_second)
{
	if (!prog || !philo)
		return ;
	pthread_mutex_lock(&prog->mutexes.forks[grab_first]);
	printf("%li %i has taken a fork\n", timestamp(prog), philo->nbr);
	pthread_mutex_lock(&prog->mutexes.forks[grab_second]);
	printf("%li %i has taken a fork\n", timestamp(prog), philo->nbr);
	philo->eat_count++;
	if (philo->eat_count == 1 && is_priority(prog, philo))
	{
		pthread_mutex_lock(prog->mutexes.eat_first_count);
		prog->eat_first_line--;
		pthread_mutex_unlock(prog->mutexes.eat_first_count);
	}
	printf("%li %i is eating\n", timestamp(prog), philo->nbr);
	usleep(prog->params.time_to_eat * 1000);	
}

void	eating_queue(t_prog *prog, t_philo *philo, int *bool_1, int *bool_2, int grab_first, int grab_second)
{
	while (1)
	{
		pthread_mutex_lock(prog->mutexes.fork_availability);
		if (*bool_1 == 0 && *bool_2 == 0)
		{
			*bool_1 = 1;
			*bool_2 = 1;
			pthread_mutex_unlock(prog->mutexes.fork_availability);
			if (philo->is_thinking)
				philo->is_thinking = 0;
			remove_queue(prog, philo);
			eating(prog, philo, grab_first, grab_second);
			pthread_mutex_lock(prog->mutexes.fork_availability);
			*bool_1 = 0;
			*bool_2 = 0;
			pthread_mutex_unlock(prog->mutexes.fork_availability);
			pthread_mutex_unlock(&prog->mutexes.forks[grab_first]);
			pthread_mutex_unlock(&prog->mutexes.forks[grab_second]);
			break ;
		}
		else
		{
			pthread_mutex_unlock(prog->mutexes.fork_availability);
			if (!philo->is_thinking)
			{
				printf("%li %i is thinking\n", timestamp(prog), philo->nbr);
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
	printf("This message should never appear");
	return (0);
}

void	philo_cicle(t_philo *philo, t_prog *prog)
{
	int	grab_first;
	int	grab_second; //put all this stuff as philo params on initilization
	int	*bool_1;
	int	*bool_2;

	if (!philo || !prog)
		return ;
	grab_first = ft_lower(philo->index, philo->index_next);
	grab_second = ft_bigger(philo->index, philo->index_next);
	bool_1 = &prog->mutexes.bool_forks[grab_first];
	bool_2 = &prog->mutexes.bool_forks[grab_second];
	while (1)
	{
		if (!philo->on_queue)
			add_queue(prog, philo);
		if (has_resource_priority(prog, philo))
		{
			eating_queue(prog, philo, bool_1, bool_2, grab_first, grab_second);
			if (prog->params.nbr_must_eat != -1 && philo->eat_count == philo->must_eat)
				break ;
			printf("%li %i is sleeping\n", timestamp(prog), philo->nbr);
			usleep(prog->params.time_to_sleep * 1000);
		}
		else
		{
			if (!philo->is_thinking)
			{
				printf("%li %i is thinking\n", timestamp(prog), philo->nbr);
				philo->is_thinking = 1;
			}
			usleep(300);
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

//Replace both usleep(300) by some proper shit, like a line 
// or shit like that, or maybe reduce time
// Do not test with time_to_die or time_to_eat or time_to_sleep set to values lower than 60 ms.
// Test 1 800 200 200. The philosopher should not eat and should die.
// Test 5 800 200 200. No philosopher should die.
// Test 5 800 200 200 7. No philosopher should die and the simulation should stop when every philosopher has eaten at least 7 times.
// Test 4 410 200 200. No philosopher should die.
// Test 4 310 200 100. One philosopher should die.
