/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeneghe <lmeneghe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 16:00:18 by lmeneghe          #+#    #+#             */
/*   Updated: 2024/08/27 17:12:19 by lmeneghe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	custom_write(t_philo *philo, char *message, t_prog *prog)
{
	sem_wait(&prog->sems.printing);
	// pthread_mutex_lock(philo->mutex_print);
	// if (!(*philo->all_alive))
	// {
	// 	philo->eat_ending_set = 1;
	// 	philo->must_eat = 0;
	// 	pthread_mutex_unlock(philo->mutex_print);
	// 	return ;
	// }
	printf("%li %i %s", timestamp(philo->strt_tm_micros, philo->tmp_time), philo->nbr, message);
	sem_post(&prog->sems.printing);
	// pthread_mutex_unlock(philo->mutex_print);
}

void	*lone_philo(t_prog *prog, int i)
{
	t_philo	*philo;

	philo = &prog->philos[i];
	philo->strt_tm_micros = prog->strt_tm_micros;
	delay_to_start(philo);
	custom_write(philo, "is thinking\n", prog);
	close_sems(prog);
	exit(0);
}
