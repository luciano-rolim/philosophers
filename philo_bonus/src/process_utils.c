/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeneghe <lmeneghe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 16:00:18 by lmeneghe          #+#    #+#             */
/*   Updated: 2024/08/28 13:08:49 by lmeneghe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	custom_write(t_philo *philo, char *message, t_prog *prog)
{
	sem_wait(prog->sems.printing);
	printf("%li %i %s", timestamp(philo->strt_tm_micros, philo->tmp_time), philo->nbr, message);
	sem_post(prog->sems.printing);
}

void	*lone_philo(t_prog *prog, int i)
{
	t_philo	*philo;

	philo = &prog->philos[i];
	prog->sems.printing = sem_open(SEM_PRINT_NAME, 0);
	delay_to_start(philo);
	custom_write(philo, "is thinking\n", prog);
	usleep(philo->time_to_die);
	custom_write(philo, "died\n", prog);
	sem_close(prog->sems.printing);
	exit(EXIT_FAILURE);
}
