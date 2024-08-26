/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_check_extra.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeneghe <lmeneghe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 15:43:16 by lmeneghe          #+#    #+#             */
/*   Updated: 2024/08/26 14:29:26 by lmeneghe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static int	check_philo_quantity(t_prog *prog)
{
	char	*message;

	if (!prog)
		return (print_error("Error on check_philo_quantity call\n"));
	if (prog->params.nbr_philos == 0)
		return (print_error("Simulation can't start without philosophers\n"));
	else if (prog->params.nbr_philos > 250)
	{
		message = "Please, don't put more than 250 philos on the simulation.";
		printf("%s This might collapse the computer!\n", message);
		return (0);
	}
	else
		return (1);
}

int	extra_checks(t_prog *prog)
{
	if (!check_philo_quantity(prog))
		return (0);
	if (prog->params.nbr_must_eat == 0)
		return (print_error("Must eat parameter is 0. Simulation aborted\n"));
	return (1);
}
