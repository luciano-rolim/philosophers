/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeneghe <lmeneghe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 09:51:37 by lmeneghe          #+#    #+#             */
/*   Updated: 2024/08/09 13:59:41 by lmeneghe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static int	start_program(t_prog *prog)
{
	int				i;
	int				function_return;

	prog->strt_tm = time_mls();
	if (prog->strt_tm == -1)
		return (print_error("Error getting start time\n"));
	prog->eat_first_line = (prog->params.nbr_philos / 2);
	i = 0;
	function_return = -1;
	while (i < prog->params.nbr_philos)
	{
		function_return = pthread_create(&prog->threads[i], NULL, \
		philo_thread, (void *)&prog->philos[i]);
		if (function_return != 0)
			return (print_error("Pthread_create failure\n"));
		i++;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_prog	prog;

	if (!check_arguments(&prog, argc, argv))
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
	usleep(500000);
	clean_prog(&prog, NULL);
	printf("Simulation finished\n");
	return (EXIT_SUCCESS);
}

//Ideias to improve performance
//Possibility to create a quickly sub-thread to perform paralell actions while eating or thinking, like to add in queue, remove from queue and shit
//ver melhor quando começar e terminar os locks