/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rest.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeneghe <lmeneghe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 09:54:50 by lmeneghe          #+#    #+#             */
/*   Updated: 2024/08/23 10:22:24 by lmeneghe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


// void	death_calculus(t_prog *prog, t_philo *philo)
// {
// 	if ((simulation_timestamp(philo->tmp_time, philo->strt_tm) - philo->last_meal) >= philo->time_to_die)
// 	{
// 		pthread_mutex_lock(prog->mutexes.printing);
// 		pthread_mutex_lock(prog->mutexes.all_alive);
// 		if (!prog->all_alive)
// 		{
// 			pthread_mutex_unlock(prog->mutexes.all_alive);	
// 			pthread_mutex_unlock(prog->mutexes.printing);
// 			return ;
// 		}
// 		prog->all_alive = 0;
// 		pthread_mutex_unlock(prog->mutexes.all_alive);
// 		printf("%li %i died\n", simulation_timestamp(philo->tmp_time, philo->strt_tm), philo->nbr);
// 		pthread_mutex_unlock(prog->mutexes.printing);
// 	}
// }


// int	think_action(t_prog *prog, t_philo *philo)
// {
// 	pthread_mutex_lock(prog->mutexes.printing);
// 	if (!prog->all_alive)
// 	{
// 		pthread_mutex_unlock(prog->mutexes.printing);
// 		return (0);
// 	}
// 	printf("%li %i is thinking\n", simulation_timestamp(philo->tmp_time, philo->strt_tm), philo->nbr);
// 	pthread_mutex_unlock(prog->mutexes.printing);
// 	return (1);
// }
