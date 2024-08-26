/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_variables.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeneghe <lmeneghe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 14:57:18 by lmeneghe          #+#    #+#             */
/*   Updated: 2024/08/26 15:11:00 by lmeneghe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	philo_variables_init(t_prog *prog, t_philo *philo, int i)
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
	return (1);
}

static int	mem_allocation(t_prog *prog)
{
	int	t_size;
	int	p_size;
	int	m_size;

	if (!prog)
		return (print_error("Error on mem_allocation function call\n"));
	t_size = sizeof(pthread_t);
	p_size = sizeof(t_philo);
	m_size = sizeof(pthread_mutex_t);
	prog->threads = ft_calloc(t_size, prog->params.nbr_philos);
	prog->philos = ft_calloc(p_size, prog->params.nbr_philos);
	prog->mutexes.forks = ft_calloc(m_size, prog->params.nbr_philos);
	if (!prog->threads || !prog->philos || !prog->mutexes.forks)
		return (print_error("Error: Allocation failure\n"));
	return (1);
}

int	start_variables(t_prog *prog)
{
	int				i;

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
