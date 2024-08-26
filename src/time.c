/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeneghe <lmeneghe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 15:37:09 by lmeneghe          #+#    #+#             */
/*   Updated: 2024/08/26 12:39:39 by lmeneghe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

long int	adjust_microseconds(long int total_time)
{
	long int	time_difference;

	time_difference = total_time % 1000;
	return (total_time - time_difference);
}

long int	time_micros(void)
{
	struct timeval tmp_time;

	gettimeofday(&tmp_time, NULL);
	return ((tmp_time.tv_sec * 1000000) + (tmp_time.tv_usec));
}

long int	time_mls(void)
{
	struct timeval tmp_time;

	gettimeofday(&tmp_time, NULL);
	return ((tmp_time.tv_sec * 1000) + (tmp_time.tv_usec / 1000));
}

long int	simulation_timestamp(long int start_time, struct timeval tmp_time, t_philo *philo)
{
	long int micro;

 	gettimeofday(&tmp_time, NULL);

	micro = (tmp_time.tv_sec * 1000000 + tmp_time.tv_usec);
	philo->surplus_time = (tmp_time.tv_usec % 1000);
	return ((micro - start_time) / 1000);
}

long int	simulation_timestamp_2(long int start_time, struct timeval tmp_time)
{
	long int micro;

 	gettimeofday(&tmp_time, NULL);

	micro = (tmp_time.tv_sec * 1000000 + tmp_time.tv_usec);
	return ((micro - start_time) / 1000);
}
