/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_check_extra.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeneghe <lmeneghe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 15:43:16 by lmeneghe          #+#    #+#             */
/*   Updated: 2024/08/23 15:45:37 by lmeneghe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static int	check_philo_quantity(t_prog *prog)
{
	if (prog->params.nbr_philos == 0)
		return (print_error("Simulation can't start without philosophers\n"));
	else if (prog->params.nbr_philos > 250)
		return (print_error("Please, don't insert more than 250 philosophers on the simulation. This might collapse the computer!\n"));
	else
		return (1);
}

int	extra_checks(t_prog *prog)
{
	if (!check_philo_quantity(prog))
		return (0);
	if (prog->params.nbr_must_eat == 0)
		return (print_error("Number of times each philosopher must eat is 0. Simulation stopped\n"));
	return (1);
}
