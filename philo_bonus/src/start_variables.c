/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_variables.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeneghe <lmeneghe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 14:57:18 by lmeneghe          #+#    #+#             */
/*   Updated: 2024/08/27 14:12:28 by lmeneghe         ###   ########.fr       */
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
	philo->prog = prog;
	philo->nbr = i + 1;
	philo->last_meal = 0;
	philo->time_to_die = prog->params.time_to_die;
	philo->time_to_eat = prog->params.time_to_eat;
	philo->time_to_sleep = prog->params.time_to_sleep;
	philo->all_alive = &prog->all_alive;
	philo->mutex_print = &prog->mutexes.printing;
	return (1);
}

static int	basic_semaphores_init(t_prog *prog)
{
	if (!prog)
		return (0);
	if (!semaphore_init(&prog->semaphores.printing))
		return (0);
	if (!semaphore_init(&prog->semaphores.counter))
		return (0);
	return (1);
}

static int	mem_allocation(t_prog *prog)
{
	int	p_size;
	int	i_size;
	int	s_size;

	if (!prog)
		return (print_error("Error on mem_allocation function call\n"));
	p_size = sizeof(t_philo);
	i_size = sizeof(int);
	s_size = sizeof(sem_t);
	prog->philo_attribution = ft_calloc(i_size, prog->params.nbr_philos);
	prog->philos = ft_calloc(p_size, prog->params.nbr_philos);
	prog->semaphores.forks = ft_calloc(s_size, prog->params.nbr_philos);
	if (!prog->philos || !prog->philo_attribution || !prog->semaphores.forks);
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
		// if (!mutex_init(&prog->mutexes.forks[i]))
		// 	return (0);
		i++;
	}
	return (1);
}
