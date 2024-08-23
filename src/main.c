/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeneghe <lmeneghe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 09:51:37 by lmeneghe          #+#    #+#             */
/*   Updated: 2024/08/23 16:17:32 by lmeneghe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static int	start_program(t_prog *prog)
{
	int				i;

	i = 0;
	prog->strt_tm = (time_mls() + 500);
	pthread_create(&prog->death_checker, NULL, death_thread, (void *)prog);
	if (prog->params.nbr_philos == 1)
		pthread_create(&prog->threads[i], NULL, lone_philo_thread, (void *)&prog->philos[i]);
	else
	{
		while (i < prog->params.nbr_philos)
		{
			pthread_create(&prog->threads[i], NULL, philo_thread, (void *)&prog->philos[i]);
			i++;
		}
	}

	// add error messages in case of pthread_create failure and stuff like that;
	// if start position equals 1 perhaps already print both forks and shit, because i know will eat
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
