/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeneghe <lmeneghe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 09:51:37 by lmeneghe          #+#    #+#             */
/*   Updated: 2024/08/26 12:28:50 by lmeneghe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static int	start_program(t_prog *prog)
{
	int	i;
	int	function_return;

	i = 0;
	function_return = -1;
	prog->strt_tm_micros = adjust_microseconds(time_micros() + 300000 + (prog->params.nbr_philos * 10000));
	function_return = pthread_create(&prog->death_checker, NULL, death_thread, (void *)prog);
	if (function_return != 0)
		return(print_error("Error initializing death_thread\n"));
	if (prog->params.nbr_philos == 1)
	{
		function_return = pthread_create(&prog->threads[i], NULL, lone_philo_thread, (void *)&prog->philos[i]);
		if (function_return != 0)
			return(print_error("Error initializing lone philo thread\n"));
	}
	else
	{
		while (i < prog->params.nbr_philos)
		{
			prog->philos[i].strt_tm_micros = prog->strt_tm_micros; 
			function_return = pthread_create(&prog->threads[i], NULL, philo_thread, (void *)&prog->philos[i]);
			if (function_return != 0)
				return(print_error("Error initializing philo threads\n"));
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
