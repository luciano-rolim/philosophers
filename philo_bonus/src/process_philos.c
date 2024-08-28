/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_philos.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeneghe <lmeneghe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 12:33:22 by lmeneghe          #+#    #+#             */
/*   Updated: 2024/08/28 17:09:56 by lmeneghe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static void	think_action(t_philo *philo, t_prog *prog)
{
	custom_write(philo, "is thinking\n", prog);
	if (philo->even_prog)
		usleep(philo->time_to_think);
	else
	{
		if (philo->wait_one_remaining > 0)
		{
			usleep(philo->time_to_think);
			philo->wait_one_remaining--;
		}
		else
		{
			usleep(philo->time_to_double_think);
			philo->wait_one_remaining = philo->max_wait_one_remaining;
		}
	}
}

static void	write_fork_eat_action(t_philo *philo, t_prog *prog)
{
	sem_wait(philo->sem_last_meal);
	sem_wait(prog->sems.printing);
	philo->last_meal = timestamp(philo->strt_tm_micros, philo->tmp_time);
	printf("%li %i has taken a fork\n%li %i is eating\n", \
	philo->last_meal, philo->nbr, philo->last_meal, philo->nbr);
	philo->must_eat--;
	sem_post(prog->sems.printing);
	sem_post(philo->sem_last_meal);
	usleep(philo->time_to_eat);
}

static void	initial_set(t_philo *philo, t_prog *prog)
{
	if (philo->start_position == 2)
	{
		delay_to_start(philo);
		custom_write(philo, "is thinking\n", prog);
		if (philo->time_to_eat > 0)
			usleep(philo->time_to_eat - TIME_REDUCE);
	}
	else if (philo->start_position == 3)
	{
		delay_to_start(philo);
		custom_write(philo, "is thinking\n", prog);
		if (philo->time_to_eat > 0)
			usleep((philo->time_to_eat * 2) - TIME_REDUCE);
	}
	else
		delay_to_start(philo);
}

int	philo_init(t_prog *prog, t_philo *philo, int i)
{
	char	*tmp_str;

	if (!prog || !philo || i < 0)
		return (print_error("Error on philo_init call\n"));
	if (!philo_variables_init(prog, philo, i))
		return (0);
	if (!start_position(prog, philo))
		return (0);
	if (!calculus_wait_one_remaining(prog, philo))
		return (0);
	if (!calculus_time_to_think(prog, philo))
		return (0);
	tmp_str = custom_itoa(philo->nbr);
	philo->sem_name_last_meal = ft_strjoin("/sem_meal_", tmp_str);
	if (tmp_str)
		free(tmp_str);
	sem_unlink(philo->sem_name_last_meal);
	if (!semaphore_init(&philo->sem_last_meal, philo->sem_name_last_meal, 1))
		return (0);
	return (1);
}

void	*philo_process(t_prog *prog, int i)
{
	t_philo	*philo;

	philo = &prog->philo;
	philo->strt_tm_micros = prog->strt_tm_micros;
	philo_init(prog, &prog->philo, i);
	pthread_create(&prog->death_checker, NULL, death_thread, philo);
	initial_set(philo, prog);
	while (1)
	{
		sem_wait(prog->sems.forks);
		custom_write(philo, "has taken a fork\n", prog);
		sem_wait(prog->sems.forks);
		write_fork_eat_action(philo, prog);
		sem_post(prog->sems.forks);
		sem_post(prog->sems.forks);
		if (philo->eat_ending_set && !philo->must_eat)
			exit_gracefully(prog, philo);
		custom_write(philo, "is sleeping\n", prog);
		usleep(philo->time_to_sleep);
		think_action(philo, prog);
	}
	exit (1);
}
