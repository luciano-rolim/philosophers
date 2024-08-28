/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_variables.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeneghe <lmeneghe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 14:57:18 by lmeneghe          #+#    #+#             */
/*   Updated: 2024/08/28 14:34:21 by lmeneghe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	philo_variables_init(t_prog *prog, t_philo *philo, int i)
{
	if (!prog || !philo)
		return (print_error("Error on philo_variables_init call\n"));
	if (prog->params.nbr_must_eat != -1)
	{
		philo->eat_ending_set = 1;
		philo->must_eat = prog->params.nbr_must_eat;
	}
	else
	{
		philo->eat_ending_set = 0;
		philo->must_eat = -1;
	}
	philo->nbr = i + 1;
	philo->prog = prog;
	philo->last_meal = 0;
	philo->time_to_die = prog->params.time_to_die;
	philo->time_to_eat = prog->params.time_to_eat;
	philo->time_to_sleep = prog->params.time_to_sleep;
	philo->all_alive = &prog->all_alive;
	return (1);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin(char const *prefix, char const *suffix)
{
	size_t	size;
	size_t	i;
	size_t	j;
	char	*new_str;

	if (!prefix || !suffix)
		return (NULL);
	size = ft_strlen(prefix) + ft_strlen(suffix) + 1;
	new_str = malloc(size);
	if (new_str == NULL)
		return (NULL);
	i = 0;
	while (prefix[i])
	{
		new_str[i] = prefix[i];
		i++;
	}
	j = 0;
	while (suffix[j])
	{
		new_str[i + j] = suffix[j];
		j++;
	}
	new_str[i + j] = '\0';
	return (new_str);
}

static int	semaphore_init(sem_t **semaphore, char *name, int value)
{
	if (!semaphore || !name || value < 0)
		return(print_error("Error on semaphore init call\n"));
	*semaphore = sem_open(name, O_CREAT, 0666, value);
	if (*semaphore == SEM_FAILED)
		return(print_error("Error on sem_open function\n"));
	return (1);
}

int	philo_init(t_prog *prog, t_philo *philo, int i)
{
	if (!prog || !philo || i < 0)
		return (print_error("Error on philo_init call\n"));
	if (!philo_variables_init(prog, philo, i))
		return (0);
	if (!start_position(prog, philo))
		return (0);
	if (!calculus_wait_one_remaining(prog, philo))
		return (0);
	if (!calculus_time_to_think(prog, philo))
		return (0);
	philo->sem_name_last_meal = ft_strjoin("/sem_meal_", custom_itoa(philo->nbr)); 
	if (!semaphore_init(&philo->sem_last_meal, philo->sem_name_last_meal, 1))
		return (0);
	return (1);
}

static int	basic_sems_init(t_prog *prog)
{
	if (!prog)
		return(print_error("Error on basic sems init call"));
	if (!semaphore_init(&prog->sems.printing, SEM_PRINT_NAME, 1))
		return (0);
	if (!semaphore_init(&prog->sems.forks, SEM_FORK_NAME, prog->params.nbr_philos))
		return (0);
	return (1);
}

// static int	mem_allocation(t_prog *prog)
// {
// 	int	p_size;

// 	if (!prog)
// 		return (print_error("Error on mem_allocation function call\n"));
// 	p_size = sizeof(t_philo);
// 	prog->philos = ft_calloc(p_size, prog->params.nbr_philos);
// 	if (!prog->philos)
// 		return (print_error("Error: Allocation failure\n"));
// 	return (1);
// }

int	start_variables(t_prog *prog)
{
	// int				i;

	if (!prog)
		return (print_error("Error on start variables call\n"));
	// if (!mem_allocation(prog))
	// 	return (0);
	unlink_sems();
	if (!basic_sems_init(prog))
		return (0);
	// i = 0;
	// while (i < prog->params.nbr_philos)
	// {
	// 	if (!philo_init(prog, &prog->philos[i], i))
	// 		return (0);
	// 	i++;
	// }
	return (1);
}
