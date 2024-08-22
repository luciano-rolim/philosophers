/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeneghe <lmeneghe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 18:21:08 by lmeneghe          #+#    #+#             */
/*   Updated: 2024/08/22 10:15:24 by lmeneghe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static void	clean_threads(t_prog *prog)
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

static void	clean_forks(t_prog *prog)
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
	// free(prog->mutexes.forks);
}

// static void	clean_and_free_mutex(pthread_mutex_t *mutex)
// {
// 	if (!mutex)
// 		return ;
// 	pthread_mutex_destroy(mutex);
// 	free(mutex);
// }

static void	clean_mutexes(t_prog *prog)
{
	if (!prog)
		return ;
	if (prog->mutexes.forks)
		clean_forks(prog);
	pthread_mutex_destroy(&prog->mutexes.all_alive);
	pthread_mutex_destroy(&prog->mutexes.printing);
}

void	clean_prog(t_prog *prog, char *message)
{
	if (!prog)
		return ;
	if (prog->threads)
		clean_threads(prog);
	clean_mutexes(prog);
	if (prog->philos)
		free(prog->philos);
	// if (prog->mutexes.bool_forks)
	// 	free(prog->mutexes.bool_forks);
	if (message)
		printf("%s\n", message);
}
