/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeneghe <lmeneghe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 10:05:55 by lmeneghe          #+#    #+#             */
/*   Updated: 2024/08/06 12:46:36 by lmeneghe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	philo_struct(t_prog *prog, int nbr, int arg)
{
	if (!prog || (arg < 1 || arg > 5))
		return (0);
	if (arg == 1)
		prog->params.nbr_philos = nbr;
	else if (arg == 2)
		prog->params.time_to_die = nbr;
	else if (arg == 3)
		prog->params.time_to_eat = nbr;
	else if (arg == 4)
		prog->params.time_to_sleep = nbr;
	else if (arg == 5)
		prog->params.nbr_must_eat = nbr;
	return (1);
}

long int	get_time_mls(void)
{
	struct timeval	tmp_time;
	int				get_time_result;
	long int		time_in_miliseconds;

	get_time_result = -1;
	get_time_result = gettimeofday(&tmp_time, NULL);
	if (get_time_result != 0)
		return (print_error("Error on gettimeofday function\n"));
	time_in_miliseconds = (tmp_time.tv_sec * 1000) + (tmp_time.tv_usec / 1000);
	return (time_in_miliseconds);
}

int	struct_malloc(t_prog *prog)
{
	int i;

	if (!prog)
		return (0);
	prog->mutexes.forks = malloc(sizeof(pthread_mutex_t) * prog->params.nbr_philos);
	prog->threads = malloc(sizeof(pthread_t) * prog->params.nbr_philos);
	prog->philos = malloc(sizeof(t_philo) * prog->params.nbr_philos);
	prog->mutexes.bool_forks = malloc(sizeof(int) * (prog->params.nbr_philos));
	prog->mutexes.fork_availability = malloc(sizeof(pthread_mutex_t));
	prog->mutexes.change_priority_count = malloc(sizeof(pthread_mutex_t));
	if (!prog->threads || !prog->mutexes.forks || !prog->philos  || \
	!prog->mutexes.bool_forks || !prog->mutexes.fork_availability || !prog->mutexes.change_priority_count)
		return (print_error("Error: Malloc failure\n"));
	i = 0;
	while (i < prog->params.nbr_philos)
		prog->mutexes.bool_forks[i++] = 0;
	return (1);
}
