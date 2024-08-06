/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_variables.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeneghe <lmeneghe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 14:57:18 by lmeneghe          #+#    #+#             */
/*   Updated: 2024/08/06 16:24:02 by lmeneghe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static int	philo_init(t_prog *prog, t_philo *philo, int i)
{
	if (!prog || !philo)
		return (print_error("Error on philo_init call\n"));
	philo->nbr = i + 1;
	philo->eat_count = 0;
	philo->prog = prog;
	philo->is_thinking = 0;
	if (prog->params.nbr_must_eat != -1)
		philo->must_eat = prog->params.nbr_must_eat;
	philo->index = i;
	if (i == (prog->params.nbr_philos - 1))
		philo->index_next = 0;
	else
		philo->index_next = i + 1;
	return (1);
}

static int	basic_mutexes_init(t_prog *prog)
{
	int	function_return;

	if (!prog)
		return (0);
	function_return = -1;
	function_return = pthread_mutex_init(prog->mutexes.fork_availability, NULL);
	if (function_return != 0)
		return (print_error("Error creating fork_availability mutex\n"));
	function_return = -1;
	function_return = pthread_mutex_init(prog->mutexes.eat_first_count, NULL);
	if (function_return != 0)
		return (print_error("Error creating eat first count mutex\n"));
	return (1);
}

static int	start_philos_mutexes(t_prog *prog)
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

static int	mem_allocation(t_prog *prog)
{
	int	t_size;
	int	m_size;
	int	i_size;
	int	p_size;

	if (!prog)
		return (print_error("Error on mem_allocation function call\n"));
	t_size = sizeof(pthread_t);
	m_size = sizeof(pthread_mutex_t);
	i_size = sizeof(int);
	p_size = sizeof(t_philo);
	prog->mutexes.forks = ft_calloc(m_size, prog->params.nbr_philos);
	prog->threads = ft_calloc(t_size, prog->params.nbr_philos);
	prog->philos = malloc(p_size * prog->params.nbr_philos);
	prog->mutexes.bool_forks = ft_calloc(i_size, (prog->params.nbr_philos));
	prog->mutexes.fork_availability = malloc(m_size);
	prog->mutexes.eat_first_count = malloc(m_size);
	if (!prog->threads || !prog->mutexes.forks || !prog->philos \
	|| !prog->mutexes.bool_forks || !prog->mutexes.fork_availability \
	|| !prog->mutexes.eat_first_count)
		return (print_error("Error: Malloc failure\n"));
	return (1);
}

int	start_variables(t_prog *prog)
{
	if (!prog)
		return (print_error("Error on start variables call\n"));
	if (!mem_allocation(prog))
		return (0);
	if (!start_philos_mutexes(prog))
		return (0);
	return (1);
}
