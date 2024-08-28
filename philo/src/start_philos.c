/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_philos.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeneghe <lmeneghe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 14:56:09 by lmeneghe          #+#    #+#             */
/*   Updated: 2024/08/28 14:46:53 by lmeneghe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	calculus_wait_one_remaining(t_prog *prog, t_philo *philo)
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

int	start_position(t_prog *prog, t_philo *philo)
{
	if (!prog || !philo)
		return (print_error("Error on start_position call\n"));
	if (is_even(philo->nbr))
		philo->start_position = 2;
	else
	{
		if (!is_even(prog->params.nbr_philos) \
		&& (philo->nbr == prog->params.nbr_philos))
			philo->start_position = 3;
		else
			philo->start_position = 1;
	}
	return (1);
}

int	grab_fork_order(t_prog *prog, t_philo *philo, int i)
{
	int	index;
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

int	odd_calculus_think_time(t_philo *philo)
{
	if (!philo)
		return (print_error("Error on odd_calculus_think_time call\n"));
	if (philo->time_to_eat > philo->time_to_sleep)
	{
		philo->time_to_think = \
		((philo->time_to_eat - philo->time_to_sleep) - TIME_REDUCE);
		philo->time_to_double_think = \
		((philo->time_to_eat * 2) - philo->time_to_sleep - TIME_REDUCE);
	}
	else if (philo->time_to_sleep == philo->time_to_eat)
	{
		philo->time_to_think = 0;
		if (philo->time_to_eat > 0)
			philo->time_to_double_think = (philo->time_to_eat - TIME_REDUCE);
		else
			philo->time_to_double_think = 0;
	}
	else
	{
		philo->time_to_think = 0;
		philo->time_to_double_think = 500;
	}
	return (1);
}

int	calculus_time_to_think(t_prog *prog, t_philo *philo)
{
	if (!prog || !philo)
		return (print_error("Error on calculus_time_to_think call\n"));
	if (is_even(prog->params.nbr_philos))
	{
		if (philo->time_to_eat > philo->time_to_sleep)
			philo->time_to_think = \
			((philo->time_to_eat - philo->time_to_sleep) - TIME_REDUCE);
		else
			philo->time_to_think = 0;
		philo->time_to_double_think = -1;
	}
	else
	{
		if (!odd_calculus_think_time(philo))
			return (0);
	}
	return (1);
}
