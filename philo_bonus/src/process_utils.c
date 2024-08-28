/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeneghe <lmeneghe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 16:00:18 by lmeneghe          #+#    #+#             */
/*   Updated: 2024/08/28 17:17:19 by lmeneghe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	children_close_sems(t_prog *prog, t_philo *philo)
{
	sem_close(prog->sems.forks);
	sem_close(prog->sems.printing);
	sem_close(philo->sem_last_meal);
}

void	custom_write(t_philo *philo, char *message, t_prog *prog)
{
	sem_wait(prog->sems.printing);
	printf("%li %i %s", timestamp(philo->strt_tm_micros, \
	philo->tmp_time), philo->nbr, message);
	sem_post(prog->sems.printing);
}

int	exit_gracefully(t_prog *prog, t_philo *philo)
{
	pthread_join(prog->death_checker, NULL);
	children_close_sems(prog, philo);
	sem_unlink(philo->sem_name_last_meal);
	if (philo->sem_name_last_meal)
		free(philo->sem_name_last_meal);
	exit(EXIT_SUCCESS);
}

void	*lone_philo(t_prog *prog, int i)
{
	t_philo	*philo;

	philo = &prog->philo;
	philo->strt_tm_micros = prog->strt_tm_micros;
	philo_init(prog, &prog->philo, i);
	delay_to_start(philo);
	custom_write(philo, "is thinking\n", prog);
	usleep(philo->time_to_die);
	custom_write(philo, "died\n", prog);
	sem_close(prog->sems.printing);
	exit(EXIT_FAILURE);
}
