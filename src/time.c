/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeneghe <lmeneghe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 15:37:09 by lmeneghe          #+#    #+#             */
/*   Updated: 2024/08/06 15:38:19 by lmeneghe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

long int	time_mls(void)
{
	struct timeval	tmp_time;
	int				get_time_result;
	long int		time_in_miliseconds;

	get_time_result = -1;
	get_time_result = gettimeofday(&tmp_time, NULL);
	if (get_time_result != 0)
		return (print_error("Error on gettimeofday function\n"));
	time_in_miliseconds = (tmp_time.tv_sec * 1000) + (tmp_time.tv_usec / 1000);
	return (time_in_miliseconds);
}

long int	timestamp(t_prog *prog)
{
	if (!prog)
		return (-1);
	return (time_mls() - prog->strt_tm);
}
