/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeneghe <lmeneghe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 09:51:37 by lmeneghe          #+#    #+#             */
/*   Updated: 2024/08/06 14:36:59 by lmeneghe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

// printf("Fork %i taken by philo %i\n", (philo->index + 1), philo->nbr);
// printf("Fork %i taken by philo %i\n", (philo->index_next + 1), philo->nbr);

int	ft_bigger(int a, int b)
{
	if (a > b)
		return (a);
	else if (b > a)
		return (b);
	else
		return (0);
}

int	ft_lower(int a, int b)
{
	if (a < b)
		return (a);
	else if (b < a)
		return (b);
	else
		return (0);
}

int	is_priority(t_prog *prog, t_philo *philo)
{
	if (!prog || !philo)
		return (-1);
	if (is_even(philo->nbr) || (philo->nbr == prog->params.nbr_philos))
		return (0);
	else
		return (1);
}

void philo_wanna_eat(t_philo *philo, t_prog *prog)
{
	int	first;
	int	second;

	first = ft_lower(philo->index, philo->index_next);
	second = ft_bigger(philo->index, philo->index_next);
	while (1)
 	{
		pthread_mutex_lock(prog->mutexes.fork_availability);
		if (prog->mutexes.bool_forks[first] == 0 && prog->mutexes.bool_forks[second] == 0)
		{
			prog->mutexes.bool_forks[first] = 1;
			prog->mutexes.bool_forks[second] = 1;
			pthread_mutex_unlock(prog->mutexes.fork_availability);
			pthread_mutex_lock(&prog->mutexes.forks[first]);
			printf("%li %i has taken a fork\n", (get_time_mls() - prog->start_time), philo->nbr);
			pthread_mutex_lock(&prog->mutexes.forks[second]);
			printf("%li %i has taken a fork\n", (get_time_mls() - prog->start_time), philo->nbr);
			philo->eat_count++;
			if (is_priority(prog, philo) && philo->eat_count == 1)
			{
				pthread_mutex_lock(prog->mutexes.change_priority_count);
				prog->priority_line_count--;
				pthread_mutex_unlock(prog->mutexes.change_priority_count);
			}
			printf("%li %i is eating\n", (get_time_mls() - prog->start_time), philo->nbr);
			usleep(prog->params.time_to_eat * 1000);
			pthread_mutex_lock(prog->mutexes.fork_availability);
			prog->mutexes.bool_forks[first] = 0;
			prog->mutexes.bool_forks[second] = 0;
			pthread_mutex_unlock(prog->mutexes.fork_availability);
			pthread_mutex_unlock(&prog->mutexes.forks[first]);
			pthread_mutex_unlock(&prog->mutexes.forks[second]);
			if (prog->params.nbr_must_eat != -1 && philo->eat_count == philo->must_eat)
				break;
			printf("%li %i is sleeping\n", (get_time_mls() - prog->start_time), philo->nbr);
			usleep(prog->params.time_to_sleep * 1000);
		}
		else
		{
			pthread_mutex_unlock(prog->mutexes.fork_availability);
			usleep(500); //Replace this shit by a proper line or shit like that, or maybe reduce time
		}
	}
}

void	*philo_thread(void *data)
{
	t_philo	*philo;
	t_prog	*prog;

	philo = (t_philo *)data;
	prog = (t_prog *)(philo->prog);
	if (!is_priority(prog, philo))
	{
		while (1)
		{
            pthread_mutex_lock(prog->mutexes.change_priority_count);
			if (prog->priority_line_count == 0)
			{            
				pthread_mutex_unlock(prog->mutexes.change_priority_count);
				break;
			}
			else
			{
				pthread_mutex_unlock(prog->mutexes.change_priority_count);
				usleep(500); //Replace this shit by a proper line or shit like that, or maybe reduce time
			}
		}
	}
	philo_wanna_eat(philo, prog);
	return (NULL);
}

int	start_program(t_prog *prog)
{
	int				i;
	int				tmp1;

	prog->start_time = get_time_mls();
	if (prog->start_time == -1)
		return (print_error("Error getting start time\n"));
	prog->priority_line_count = (prog->params.nbr_philos / 2);
	i = 0;
	tmp1 = -1;
	while (i < prog->params.nbr_philos)
	{
		tmp1 = pthread_create(&prog->threads[i], NULL, philo_thread, (void *)&prog->philos[i]);
		if (tmp1 != 0)
			return (print_error("Pthread_create failure\n"));
		i++;
	}
	return (1);
}

int	basic_mutexes_init(t_prog *prog)
{
	int	function_return;

	if (!prog)
		return (0);
	function_return = -1;
	function_return = pthread_mutex_init(prog->mutexes.fork_availability, NULL);
	if (function_return != 0)
		return (print_error("Error creating fork_availability mutex\n"));
	function_return = pthread_mutex_init(prog->mutexes.change_priority_count, NULL);
	if (function_return != 0)
		return (print_error("Error creating priority line mutex\n"));
	return (1);
}

int	philo_init(t_prog *prog, t_philo *philo, int i)
{
	if (!prog || !philo)
		return (print_error("Error on philo_init call\n"));
	philo->nbr = i + 1;
	philo->eat_count = 0;
	philo->prog = prog;
	if (prog->params.nbr_must_eat != -1)
		philo->must_eat = prog->params.nbr_must_eat;
	philo->index = i;
	if (i == (prog->params.nbr_philos - 1))
		philo->index_next = 0;
	else
		philo->index_next = i + 1;
	return (1);
}

int	start_philos_mutexes(t_prog *prog)
{
	int	i;
	int	function_return;

	if (!prog)
		return (print_error("Error on start_philos_mutexes call\n"));
	if (!basic_mutexes_init(prog))
		return (0);
	i = 0;
	function_return = -1;
	while (i < prog->params.nbr_philos)
	{
		if (!philo_init(prog, &prog->philos[i], i))
			return (0);
		function_return = pthread_mutex_init(&prog->mutexes.forks[i], NULL);
		if (function_return != 0)
			return (print_error("Pthread_mutex_init failure\n"));
		i++;
	}
	return (1);
}

int	start_variables(t_prog *prog)
{
	if (!prog)
		return(print_error("Error on start variables call\n"));
	if (!struct_malloc(prog))
		return (0);
	if (!start_philos_mutexes(prog))
		return (0);
	return (1);
}

int	main(int argc, char **argv)
{
	t_prog	prog;

	if (!check_arguments(&prog, argc, argv))
		return (EXIT_FAILURE);
	if (!start_variables(&prog))
	{
		clean_prog(&prog, NULL);
		return (EXIT_FAILURE);
	}
	if (!start_program(&prog))
	{
		clean_prog(&prog, NULL);
		return (EXIT_FAILURE);
	}
	usleep(500000);
	clean_prog(&prog, NULL);
	printf("Simulation finished\n");
	return (EXIT_SUCCESS);
}
