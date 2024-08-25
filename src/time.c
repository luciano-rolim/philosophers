/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeneghe <lmeneghe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 15:37:09 by lmeneghe          #+#    #+#             */
/*   Updated: 2024/08/25 12:05:30 by lmeneghe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

long int	time_mls(void)
{
	struct timeval tmp_time;

	gettimeofday(&tmp_time, NULL);
	return ((tmp_time.tv_sec * 1000) + (tmp_time.tv_usec / 1000));
}

long int	simulation_timestamp(long int start_time, struct timeval tmp_time)
{
 	gettimeofday(&tmp_time, NULL);
	return (((tmp_time.tv_sec * 1000) + (tmp_time.tv_usec / 1000)) - start_time);
}
