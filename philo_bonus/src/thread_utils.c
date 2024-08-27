/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeneghe <lmeneghe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 16:00:18 by lmeneghe          #+#    #+#             */
/*   Updated: 2024/08/27 10:29:39 by lmeneghe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	custom_write(t_philo *philo, char *message)
{
	pthread_mutex_lock(philo->mutex_print);
	if (!(*philo->all_alive))
	{
		philo->eat_ending_set = 1;
		philo->must_eat = 0;
		pthread_mutex_unlock(philo->mutex_print);
		return ;
	}
	printf("%li %i %s", \
	timestamp(philo->strt_tm_micros, philo->tmp_time), philo->nbr, message);
	pthread_mutex_unlock(philo->mutex_print);
}

void	*lone_philo(void *data)
{
	t_philo	*philo;
	t_prog	*prog;

	philo = (t_philo *)data;
	prog = (t_prog *)philo->prog;
	philo->strt_tm_micros = prog->strt_tm_micros;
	delay_to_start(philo);
	custom_write(philo, "is thinking\n");
	return (NULL);
}
