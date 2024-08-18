/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeneghe <lmeneghe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 09:51:37 by lmeneghe          #+#    #+#             */
/*   Updated: 2024/08/17 15:16:11 by lmeneghe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static int	start_program(t_prog *prog)
{
	int				i;

	i = -1;
	prog->strt_tm = time_mls();
	while (++i < prog->params.nbr_philos)
		pthread_create(&prog->threads[i], NULL, philo_thread, (void *)&prog->philos[i]);
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
	// int i = 0;
	// while (i < prog.params.nbr_philos)
	// {
	// 	printf("Philo %i has start position of %i and wait 1 remaning of %i\n", prog.philos[i].nbr, prog.philos[i].start_position, prog.philos[i].wait_one_remaining);
	// 	i++;
	// }
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

//ver melhor quando começar e terminar os locks

//ver alguma forma de inicializar as threads que nao seja com essa porra de loop while do caracas, possivelmente uma sub thread de inicializacao sei la
//Criar porcaria do caracas para inicializar 4 threads ao mesmo tempo e assim otimizar comeco
//shit scenario of only 1 philosopher
