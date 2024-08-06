/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeneghe <lmeneghe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 18:21:08 by lmeneghe          #+#    #+#             */
/*   Updated: 2024/08/06 12:46:36 by lmeneghe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	clean_forks(t_prog *prog)
{
	int	i;

	if (!prog || !prog->mutexes.forks)
		return ;
	if (prog->params.nbr_philos != -1)
	{
		i = 0;
		while (i < prog->params.nbr_philos)
			pthread_mutex_destroy(&prog->mutexes.forks[i++]);
	}
	free(prog->mutexes.forks);
}

void	clean_threads(t_prog *prog)
{
	int	i;

	if (!prog || !prog->threads)
		return ;
	if (prog->params.nbr_philos != -1)
	{
		i = 0;
		while (i < prog->params.nbr_philos && prog->threads[i])
			pthread_join(prog->threads[i++], NULL);
	}
	free(prog->threads);
}

void	clean_prog(t_prog *prog, char *message)
{
	if (!prog)
		return ;
	if (prog->threads)
		clean_threads(prog);
	if (prog->mutexes.forks)
		clean_forks(prog);
	if (prog->philos)
		free(prog->philos);
	if (prog->mutexes.bool_forks)
		free(prog->mutexes.bool_forks);
	if (prog->mutexes.fork_availability) //increment custom function when more mutexes
	{
		pthread_mutex_destroy(prog->mutexes.fork_availability);
		free(prog->mutexes.fork_availability);
	}
	if (prog->mutexes.change_priority_count) //increment custom function when more mutexes
	{
		pthread_mutex_destroy(prog->mutexes.change_priority_count);
		free(prog->mutexes.change_priority_count);
	}
	if (message)
		printf("%s\n", message);
}
