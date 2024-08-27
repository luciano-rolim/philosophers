/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeneghe <lmeneghe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 15:37:09 by lmeneghe          #+#    #+#             */
/*   Updated: 2024/08/27 16:32:52 by lmeneghe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

long int	time_in_microseconds(void)
{
	struct timeval	tmp_time;

	gettimeofday(&tmp_time, NULL);
	return ((tmp_time.tv_sec * 1000000) + (tmp_time.tv_usec));
}

long int	timestamp(long int start_time, struct timeval tmp_time)
{
	long int	total_microseconds;

	gettimeofday(&tmp_time, NULL);
	total_microseconds = (tmp_time.tv_sec * 1000000 + tmp_time.tv_usec);
	return ((total_microseconds - start_time) / 1000);
}

long int	program_start_time(t_prog *prog)
{
	long int	start_time;

	start_time = time_in_microseconds();
	start_time += 300000;
	start_time += (prog->params.nbr_philos * 10000);
	start_time -= (start_time % 1000);
	return (start_time);
}

void	delay_to_start(t_philo *philo)
{
	while (time_in_microseconds() < philo->strt_tm_micros)
		continue ;
}
