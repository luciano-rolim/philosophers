/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeneghe <lmeneghe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 18:21:08 by lmeneghe          #+#    #+#             */
/*   Updated: 2024/08/25 11:43:38 by lmeneghe         ###   ########.fr       */
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
		{
			pthread_join(prog->threads[i], NULL);
			pthread_mutex_destroy(&prog->philos[i].mutex_last_meal);
			i++;
		}
	}
	if (prog->threads)
		free(prog->threads);
}

static void	clean_mutexes(t_prog *prog)
{
	int	i;

	if (!prog)
		return ;
	if (prog->params.nbr_philos != -1)
	{
		i = 0;
		while (i < prog->params.nbr_philos)
			pthread_mutex_destroy(&prog->mutexes.forks[i++]);
	}
	pthread_mutex_destroy(&prog->mutexes.all_alive);
	pthread_mutex_destroy(&prog->mutexes.printing);
}

void	clean_prog(t_prog *prog, char *message)
{
	if (!prog)
		return ;
	pthread_join(prog->death_checker, NULL);
	if (prog->threads)
		clean_threads(prog);
	clean_mutexes(prog);
	if (prog->philos)
		free(prog->philos);
	if (message)
		printf("%s\n", message);
}
