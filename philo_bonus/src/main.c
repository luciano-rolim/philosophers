/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeneghe <lmeneghe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 09:51:37 by lmeneghe          #+#    #+#             */
/*   Updated: 2024/08/29 10:37:06 by lmeneghe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static void	wait_children_return(t_prog *prog)
{
	int		running_children;
	int		i;
	int		status;
	pid_t	pid;

	i = 0;
	running_children = prog->params.nbr_philos;
	while (running_children != 0)
	{
		pid = waitpid(-1, &status, 0);
		status = WEXITSTATUS(status);
		if (status != 0)
		{
			while (i < prog->params.nbr_philos)
			{
				if (prog->pids[i] != pid)
					kill(prog->pids[i], SIGKILL);
				i++;
			}
			break ;
		}
		else
			running_children--;
	}
}

static int	start_program(t_prog *prog)
{
	int		i;

	i = 0;
	prog->strt_tm_micros = program_start_time(prog);
	while (i < prog->params.nbr_philos)
	{
		prog->pids[i] = fork();
		if (prog->pids[i] == -1)
			return (print_error("Error on fork function\n"));
		else if (prog->pids[i] == 0)
		{
			if (prog->params.nbr_philos == 1)
				lone_philo(prog, i);
			else
				philo_process(prog, i);
		}
		else
			i++;
	}
	wait_children_return(prog);
	return (1);
}

int	main(int argc, char **argv)
{
	static t_prog	prog;

	if (!check_arguments(&prog, argc, argv))
		return (EXIT_FAILURE);
	if (!extra_checks(&prog))
		return (EXIT_FAILURE);
	if (!start_variables(&prog))
	{
		clean_prog(&prog, NULL);
		return (EXIT_FAILURE);
	}
	if (!start_program(&prog))
	{
		clean_prog(&prog, NULL);
		return (EXIT_FAILURE);
	}
	clean_prog(&prog, NULL);
	return (EXIT_SUCCESS);
}
