/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeneghe <lmeneghe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 10:05:55 by lmeneghe          #+#    #+#             */
/*   Updated: 2024/08/23 12:06:21 by lmeneghe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	param_attribution(t_prog *prog, int nbr, int arg)
{
	if (!prog || (arg < 1 || arg > 5))
		return (0);
	if (arg == 1)
		prog->params.nbr_philos = nbr;
	else if (arg == 2)
		prog->params.time_to_die = (nbr * 1000);
	else if (arg == 3)
		prog->params.time_to_eat = (nbr * 1000);
	else if (arg == 4)
		prog->params.time_to_sleep = (nbr * 1000);
	else if (arg == 5)
		prog->params.nbr_must_eat = nbr;
	return (1);
}

int	print_error(char *message)
{
	if (!message)
		return (0);
	printf("%s", message);
	return (0);
}

void	*print_error_pointer(char *message)
{
	if (!message)
		return (NULL);
	printf("%s", message);
	return (NULL);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	full_size;
	size_t	i;
	void	*ptr;

	if (nmemb == 0 || size == 0)
	{
		ptr = malloc(0);
		if (!ptr)
			return (NULL);
		return (ptr);
	}
	full_size = nmemb * size;
	if (full_size / size != nmemb)
		return (NULL);
	ptr = malloc(full_size);
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < full_size)
		((unsigned char *)ptr)[i++] = 0;
	return (ptr);
}

// int	eat_first_priority(t_prog *prog, t_philo *philo)
// {
// 	if (!prog || !philo)
// 		return (-1);
// 	if (is_even(philo->nbr) || (philo->nbr == prog->params.nbr_philos))
// 		philo->eat_first_priority = 0;
// 	else
// 		philo->eat_first_priority = 1;
// 	return (1);
// }
