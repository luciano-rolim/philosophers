/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeneghe <lmeneghe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 18:21:08 by lmeneghe          #+#    #+#             */
/*   Updated: 2024/08/27 17:12:04 by lmeneghe         ###   ########.fr       */
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

// static void	clean_mutexes(t_prog *prog)
// {
// 	int	i;

// 	if (!prog)
// 		return ;
// 	if (prog->params.nbr_philos != -1)
// 	{
// 		i = 0;
// 		while (i < prog->params.nbr_philos)
// 			pthread_mutex_destroy(&prog->mutexes.forks[i++]);
// 	}
// 	if (prog->mutexes.forks)
// 		free(prog->mutexes.forks);
// 	pthread_mutex_destroy(&prog->mutexes.printing);
// }

void	unlink_sems(void)
{
	sem_unlink(SEM_FORK_NAME);
	sem_unlink(SEM_PRINT_NAME);
}

void	close_sems(t_prog *prog)
{
	sem_close(&prog->sems.forks);
	sem_close(&prog->sems.printing);
}

void	clean_prog(t_prog *prog, char *message)
{
	if (!prog)
		return ;
	pthread_join(prog->death_checker, NULL);
	if (prog->threads)
		clean_threads(prog);
	// clean_mutexes(prog);
	if (prog->philos)
		free(prog->philos);
	close_sems(prog);
	unlink_sems();
	if (message)
		printf("%s\n", message);
}
