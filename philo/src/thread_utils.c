/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeneghe <lmeneghe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 16:00:18 by lmeneghe          #+#    #+#             */
/*   Updated: 2024/08/28 11:24:37 by lmeneghe         ###   ########.fr       */
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

	philo = (t_philo *)data;
	delay_to_start(philo);
	custom_write(philo, "is thinking\n");
	return (NULL);
}
