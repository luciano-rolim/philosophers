/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeneghe <lmeneghe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 09:51:37 by lmeneghe          #+#    #+#             */
/*   Updated: 2024/08/28 13:30:19 by lmeneghe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static int	start_program(t_prog *prog)
{
	int		i;
    int		status;
	int		running_children;
    pid_t	pid;
	pid_t	pids[prog->params.nbr_philos];

	i = 0;
	prog->strt_tm_micros = program_start_time(prog);
	while (i < prog->params.nbr_philos)
	{
		prog->philos[i].strt_tm_micros = prog->strt_tm_micros;
		pids[i] = fork();
		if (pids[i] == -1)
			return(print_error("Error on fork function\n"));
		else if (pids[i] == 0)
		{
			if (prog->params.nbr_philos == 1)
				lone_philo(prog, i);
			else
				philo_process(prog, i);					
		}
		else
			i++;
	}
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
				if (pids[i] != pid)
					kill(pids[i], SIGKILL);
				i++;
			}
			break ;
		}
		else
			running_children--;
	}
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
