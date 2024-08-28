/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeneghe <lmeneghe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 18:21:08 by lmeneghe          #+#    #+#             */
/*   Updated: 2024/08/28 14:32:08 by lmeneghe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	unlink_sems(void)
{
	sem_unlink(SEM_FORK_NAME);
	sem_unlink(SEM_PRINT_NAME);
}

static void	parent_close_sems(t_prog *prog)
{
	sem_close(prog->sems.forks);
	sem_close(prog->sems.printing);
}

void	clean_prog(t_prog *prog, char *message)
{
	if (!prog)
		return ;
	parent_close_sems(prog);
	unlink_sems();
	if (message)
		printf("%s\n", message);
}
