/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeneghe <lmeneghe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 09:51:37 by lmeneghe          #+#    #+#             */
/*   Updated: 2024/08/26 15:31:12 by lmeneghe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static int	init_thread(pthread_t *thread, void *(*func) (void *), void *data)
{
	int	function_return;

	function_return = -1;
	function_return = pthread_create(thread, NULL, func, data);
	if (function_return != 0)
		return (print_error("Error initializing thread\n"));
	return (1);
}

static int	start_program(t_prog *prog)
{
	int	i;

	i = 0;
	prog->strt_tm_micros = program_start_time(prog);
	if (!init_thread(&prog->death_checker, death_thread, prog))
		return (0);
	if (prog->params.nbr_philos == 1)
	{
		if (!init_thread(&prog->threads[i], lone_philo, \
		(void *)&prog->philos[i]))
			return (0);
	}
	else
	{
		while (i < prog->params.nbr_philos)
		{
			prog->philos[i].strt_tm_micros = prog->strt_tm_micros;
			if (!init_thread(&prog->threads[i], philo_thread, \
			(void *)&prog->philos[i]))
				return (0);
			i++;
		}
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
