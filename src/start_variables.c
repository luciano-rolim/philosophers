/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_variables.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeneghe <lmeneghe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 14:57:18 by lmeneghe          #+#    #+#             */
/*   Updated: 2024/08/23 16:36:16 by lmeneghe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static void calculus_wait_one_remaining(t_prog *prog, t_philo *philo)
{
	if (!prog || !philo)
		return ;
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
}
static void start_position(t_prog *prog, t_philo *philo)
{
	if (!prog || !philo)
		return ;
	if (is_even(philo->nbr))
		philo->start_position = 2;
	else
	{
		if (!is_even(prog->params.nbr_philos) && (philo->nbr == prog->params.nbr_philos))
			philo->start_position = 3;
		else
			philo->start_position = 1;
	}
}

void	grab_fork_order(t_prog *prog, t_philo *philo)
{
	if (is_even(philo->nbr))
	{
		philo->grab_first = &prog->mutexes.forks[philo->index_next];
		philo->grab_second = &prog->mutexes.forks[philo->index];
	}
	else
	{
		philo->grab_first = &prog->mutexes.forks[philo->index];
		if (philo->nbr == prog->params.nbr_philos)
			philo->grab_second = &prog->mutexes.forks[0];			
		else
			philo->grab_second = &prog->mutexes.forks[philo->index_next];
	}
}

static int	philo_init(t_prog *prog, t_philo *philo, int i)
{
	if (!prog || !philo)
		return (print_error("Error on philo_init call\n"));

	philo->nbr = i + 1;
	philo->eat_count = 0;
	philo->prog = prog;

	if (prog->params.nbr_must_eat != -1)
	{
		philo->eat_ending_set = 1;
		philo->must_eat = prog->params.nbr_must_eat;
	}
	else
		philo->eat_ending_set = 0;
	philo->index = i;
	if (i == (prog->params.nbr_philos - 1))
		philo->index_next = 0;
	else
		philo->index_next = i + 1;



	grab_fork_order(prog, philo);
	start_position(prog, philo);
	calculus_wait_one_remaining(prog, philo);

	philo->last_meal = 0;
	philo->time_to_die = prog->params.time_to_die;
	philo->time_to_eat = prog->params.time_to_eat;
	philo->time_to_sleep = prog->params.time_to_sleep;
	philo->all_alive = &prog->all_alive;
	philo->mutex_print = &prog->mutexes.printing;
	philo->mutex_all_alive = &prog->mutexes.all_alive;
	pthread_mutex_init(&philo->mutex_last_meal, NULL);
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
