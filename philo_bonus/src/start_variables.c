/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_variables.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeneghe <lmeneghe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 14:57:18 by lmeneghe          #+#    #+#             */
/*   Updated: 2024/08/28 17:11:43 by lmeneghe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	semaphore_init(sem_t **semaphore, char *name, int value)
{
	if (!semaphore || !name || value < 0)
		return (print_error("Error on semaphore init call\n"));
	*semaphore = sem_open(name, O_CREAT, 0644, value);
	if (*semaphore == SEM_FAILED)
		return (print_error("Error on sem_open function\n"));
	return (1);
}

static int	basic_sems_init(t_prog *prog)
{
	if (!prog)
		return (print_error("Error on basic sems init call"));
	if (!semaphore_init(&prog->sems.printing, SEM_PRINT_NAME, 1))
		return (0);
	if (!semaphore_init(&prog->sems.forks, SEM_FORK_NAME, \
	prog->params.nbr_philos))
		return (0);
	return (1);
}

int	start_variables(t_prog *prog)
{
	if (!prog)
		return (print_error("Error on start variables call\n"));
	unlink_sems();
	if (!basic_sems_init(prog))
		return (0);
	return (1);
}
