/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_variables.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeneghe <lmeneghe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 14:57:18 by lmeneghe          #+#    #+#             */
/*   Updated: 2024/08/25 11:57:15 by lmeneghe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static int	calculus_wait_one_remaining(t_prog *prog, t_philo *philo)
{
	if (!prog || !philo)
		return (print_error("Error on calculus_wait_one_remaining call\n"));
	if (is_even(prog->params.nbr_philos))
	{
		philo->even_prog = 1;
		philo->wait_one_remaining = -1;
		philo->max_wait_one_remaining = -1;
	}
	else
	{
		philo->max_wait_one_remaining = ((prog->params.nbr_philos / 2) - 1);
		philo->even_prog = 0;
		if (philo->nbr <= 2)
			philo->wait_one_remaining = 0;
		else if (is_even(philo->nbr) || philo->nbr == prog->params.nbr_philos)
			philo->wait_one_remaining = ((philo->nbr / 2) - 1);
		else
			philo->wait_one_remaining = (philo->nbr / 2);
	}
	return (1);
}

static int	start_position(t_prog *prog, t_philo *philo)
{
	if (!prog || !philo)
		return (print_error("Error on start_position call\n"));
	if (is_even(philo->nbr))
		philo->start_position = 2;
	else
	{
		if (!is_even(prog->params.nbr_philos) && (philo->nbr == prog->params.nbr_philos))
			philo->start_position = 3;
		else
			philo->start_position = 1;
	}
	return (1);
}

int	grab_fork_order(t_prog *prog, t_philo *philo, int i)
{
	int index;
	int	index_next;

	if (!prog || !philo || i < 0)
		return (print_error("Error on grab_fork_order call\n"));
	index = i;
	if (i == (prog->params.nbr_philos - 1))
		index_next = 0;
	else
		index_next = i + 1;
	if (is_even(philo->nbr))
	{
		philo->grab_first = &prog->mutexes.forks[index_next];
		philo->grab_second = &prog->mutexes.forks[index];
	}
	else
	{
		philo->grab_first = &prog->mutexes.forks[index];
		philo->grab_second = &prog->mutexes.forks[index_next];
	}
	return (1);
}

static int philo_variables_init(t_prog *prog, t_philo *philo, int i)
{
	if (!prog || !philo)
		return (print_error("Error on philo_variables_init call\n"));
	if (prog->params.nbr_must_eat != -1)
	{
		philo->eat_ending_set = 1;
		philo->must_eat = prog->params.nbr_must_eat;
	}
	else
	{
		philo->eat_ending_set = 0;
		philo->must_eat = -1;
	}
	philo->nbr = i + 1;
	philo->prog = prog;
	philo->last_meal = 0;
	philo->time_to_die = prog->params.time_to_die;
	philo->time_to_eat = prog->params.time_to_eat;
	philo->time_to_sleep = prog->params.time_to_sleep;
	philo->all_alive = &prog->all_alive;
	philo->mutex_print = &prog->mutexes.printing;
	philo->mutex_all_alive = &prog->mutexes.all_alive;
	return (1);
}

static int calculus_time_to_think(t_prog *prog, t_philo *philo)
{
	if (!prog || !philo)
		return (print_error("Error on calculus_time_to_think call\n"));
	if (is_even(prog->params.nbr_philos))
	{
		if (philo->time_to_eat > philo->time_to_sleep)
			philo->time_to_think = ((philo->time_to_eat - philo->time_to_sleep) - 900);		
		else
			philo->time_to_think = 0;
		philo->time_to_double_think = -1;
	}
	else
	{
		if (philo->time_to_eat > philo->time_to_sleep)
		{
			philo->time_to_think = ((philo->time_to_eat - philo->time_to_sleep) - 900);
			philo->time_to_double_think = ((philo->time_to_eat * 2) - philo->time_to_sleep - 900);
		}
		else if (philo->time_to_sleep == philo->time_to_eat)
		{
			philo->time_to_think = 0;
			if (philo->time_to_eat > 0)
				philo->time_to_double_think = (philo->time_to_eat - 900);
			else
				philo->time_to_double_think = 0;
		}
		else
		{
			philo->time_to_think = 0;
			philo->time_to_double_think = 500;
		}
	}
	return (1);
}

static int	philo_init(t_prog *prog, t_philo *philo, int i)
{
	if (!prog || !philo || i < 0)
		return (print_error("Error on philo_init call\n"));
	if (!philo_variables_init(prog, philo, i))
		return (0);
	if (!grab_fork_order(prog, philo, i))
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

static int	basic_mutexes_init(t_prog *prog)
{
	if (!prog)
		return (0);
	if (!mutex_init(&prog->mutexes.printing))
		return (0);
	if (!mutex_init(&prog->mutexes.all_alive))
		return (0);
	return (1);
}

static int	mem_allocation(t_prog *prog)
{
	int	t_size;
	int	p_size;

	if (!prog)
		return (print_error("Error on mem_allocation function call\n"));
	t_size = sizeof(pthread_t);
	p_size = sizeof(t_philo);
	prog->threads = ft_calloc(t_size, prog->params.nbr_philos);
	prog->philos = ft_calloc(p_size, prog->params.nbr_philos);
	if (!prog->threads || !prog->philos)
		return (print_error("Error: Malloc failure\n"));
	return (1);
}

int	start_variables(t_prog *prog)
{
	int	i;

	if (!prog)
		return (print_error("Error on start variables call\n"));
	if (!mem_allocation(prog))
		return (0);
	if (!basic_mutexes_init(prog))
		return (0);
	i = 0;
	while (i < prog->params.nbr_philos)
	{
		if (!philo_init(prog, &prog->philos[i], i))
			return (0);
		if (!mutex_init(&prog->mutexes.forks[i]))
			return (0);
		i++;
	}
	return (1);
}
